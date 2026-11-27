#!/usr/bin/env python3
"""Arduino Zero→Hero — Lesson Flasher

Double-clickable GUI: pick a lesson, pick the board's serial port, Upload.

No Arduino IDE / arduino-cli required:
  - flashes the prebuilt build/<lesson>.hex files
  - uses a bundled/system avrdude when available, otherwise a pure-Python
    STK500 uploader (needs pyserial)

CLI mode (no display needed):
  flasher.py --cli                 # interactive menu
  flasher.py --cli 03_piano        # flash directly
  flasher.py --cli 03_piano --port /dev/ttyUSB0
"""
import argparse
import glob
import os
import queue
import subprocess
import sys
import threading
import time

try:
    import tkinter as tk
    from tkinter import messagebox, scrolledtext, ttk
except ImportError:  # headless / cli-only environments
    tk = None

BASE = getattr(sys, "_MEIPASS", os.path.dirname(os.path.abspath(__file__)))
HEXDIR = os.path.join(BASE, "build")
if not os.path.isdir(HEXDIR):  # running from repo checkout
    HEXDIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "build")

MCU, PROGRAMMER, BAUD = "atmega328p", "arduino", "115200"

LESSONS = [
    ("01_traffic_light",    "Traffic Light",            "Red/yellow/green LED sequence, digital output"),
    ("02_dimmer_led",       "Dimmer Lamp",              "Potentiometer -> PWM brightness, analog input"),
    ("03_piano",            "Mini Piano",               "Pushbuttons + buzzer tones"),
    ("04_night_light",      "Automatic Night Light",    "LDR light sensor + threshold"),
    ("05_digital_dice",     "Digital Dice",             "1-digit 7-segment + random roll"),
    ("06_led_meter",        "LED Light Meter",          "74HC595 shift register + 8-LED bar graph"),
    ("07_remote_neopixel",  "Remote NeoPixel Lamp",     "IR remote + WS2812 ring colors/effects"),
    ("08_countdown_timer",  "Countdown Timer",          "4-digit 7-seg multiplexing + buzzer"),
    ("09_stepper_motor",    "Stepper Motor",            "28BYJ-48 + ULN2003, coil sequencing"),
    ("10_rfid_access",      "RFID Access Control",      "RC522 + NeoPixel feedback + relay"),
    ("11_smart_door_lock",  "Smart Door Lock",          "RFID + IR-PIN + LCD + servo (capstone)"),
]


# ---------------------------------------------------------------- utils

def find_avrdude():
    """Return (binary, conf) or None. Bundled > PATH > arduino-cli toolchain."""
    cand = [
        (os.path.join(BASE, "avrdude"), os.path.join(BASE, "avrdude.conf")),
        ("/usr/bin/avrdude", None),
        ("/usr/local/bin/avrdude", None),
    ]
    for b in glob.glob(os.path.expanduser(
            "~/.arduino15/packages/arduino/tools/avrdude/*/bin/avrdude*")):
        cand.append((b, os.path.join(os.path.dirname(os.path.dirname(b)),
                                     "etc", "avrdude.conf")))
    for b, c in cand:
        if os.path.isfile(b) and os.access(b, os.X_OK):
            return b, (c if c and os.path.isfile(c) else None)
    return None


def list_ports():
    """Return [(device, description)], real USB-serial devices first.

    pyserial lists phantom onboard /dev/ttyS* UARTs too — those are filtered
    out unless nothing else exists (then we show everything)."""
    try:
        from serial.tools import list_ports as lp
        ports = [(p.device, p.description or p.device) for p in lp.comports()]
    except ImportError:
        devs = sorted(glob.glob("/dev/ttyACM*") + glob.glob("/dev/ttyUSB*"))
        ports = [(d, d) for d in devs]
    real = [p for p in ports
            if "ttyS" not in p[0].rsplit("/", 1)[-1] or "ttyACM" in p[0] or "ttyUSB" in p[0]]
    return real or ports


def parse_hex(path):
    """Intel HEX -> contiguous bytes (0xFF-padded)."""
    data = {}
    upper = 0
    with open(path) as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            if not line.startswith(":"):
                raise ValueError(f"bad hex line: {line!r}")
            raw = bytes.fromhex(line[1:])
            count, addr, rtype = raw[0], (raw[1] << 8) | raw[2], raw[3]
            if rtype == 0x00:
                for i, b in enumerate(raw[4:4 + count]):
                    data[upper + addr + i] = b
            elif rtype == 0x01:
                break
            elif rtype == 0x04:
                upper = ((raw[4] << 8) | raw[5]) << 16
    if not data:
        raise ValueError("empty hex file")
    lo, hi = min(data), max(data)
    return bytes(data.get(a, 0xFF) for a in range(lo, hi + 1)), lo


# ---------------------------------------------------------------- flashing

def flash_avrdude(avrdude, conf, port, hexfile, log):
    cmd = [avrdude]
    if conf:
        cmd += ["-C", conf]
    cmd += ["-p", MCU, "-c", PROGRAMMER, "-P", port, "-b", BAUD,
            "-D", "-U", f"flash:w:{hexfile}:i"]
    log("$ " + " ".join(cmd))
    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT, text=True)
    for line in proc.stdout:
        log(line.rstrip())
    proc.wait()
    if proc.returncode != 0:
        raise RuntimeError(f"avrdude exited with code {proc.returncode}")


def _stk_cmd(ser, payload):
    ser.write(bytes(payload) + b"\x20")
    r = ser.read(2)
    if len(r) != 2 or r[0] != 0x14 or r[1] != 0x10:
        raise IOError(f"stk500: bad response {r!r}")


def flash_stk500(port, hexfile, log):
    """Pure-Python STK500v1 uploader (optiboot / Arduino Uno bootloader)."""
    import serial
    image, start = parse_hex(hexfile)
    log(f"opening {port} @ {BAUD} (STK500v1, {len(image)} bytes @ 0x{start:04x})")
    ser = serial.Serial(port, BAUD, timeout=1)
    try:
        ser.dtr = False
        ser.rts = False
        time.sleep(0.05)
        ser.dtr = True
        ser.rts = True
        time.sleep(0.05)
        ser.reset_input_buffer()
        for attempt in range(20):
            try:
                _stk_cmd(ser, [0x30])          # STK_GET_SYNC
                break
            except IOError:
                ser.reset_input_buffer()
                time.sleep(0.05)
        else:
            raise IOError("board did not enter bootloader — check port/board")
        _stk_cmd(ser, [0x50])                  # STK_ENTER_PROGMODE
        for off in range(0, len(image), 128):
            page = image[off:off + 128].ljust(128, b"\xff")
            addr = (start + off) // 2          # word address
            _stk_cmd(ser, [0x55, addr & 0xFF, addr >> 8])
            _stk_cmd(ser, [0x64, 0, 128, 0x46] + list(page))
            if off % 1024 == 0:
                log(f"  wrote {off + 128}/{len(image)} bytes")
        _stk_cmd(ser, [0x51])                  # STK_LEAVE_PROGMODE
    finally:
        ser.close()
    log("flash complete")


def flash(port, hexfile, log):
    avrdude = find_avrdude()
    if avrdude:
        flash_avrdude(avrdude[0], avrdude[1], port, hexfile, log)
        return
    try:
        import serial  # noqa: F401
    except ImportError:
        raise RuntimeError(
            "no avrdude and no pyserial — install one of them:\n"
            "  sudo dnf install avrdude    (or apt install avrdude)\n"
            "  pip install --user pyserial")
    flash_stk500(port, hexfile, log)


# ---------------------------------------------------------------- GUI

ACCENT, ACCENT_DIM = "#16a34a", "#9ca3af"
LOG_BG, LOG_FG = "#1c1c1e", "#d4d4d4"


def run_gui(ontop=False):
    root = tk.Tk()
    root.title("Arduino Zero→Hero — Lesson Flasher")
    root.minsize(560, 560)
    if ontop:
        root.attributes("-topmost", True)
    q = queue.Queue()
    state = {"flashing": False}

    def log(msg):
        q.put(("log", msg))

    def drain():
        while True:
            try:
                kind, msg = q.get_nowait()
            except queue.Empty:
                break
            if kind == "log":
                tag = "err" if "error" in msg.lower() or msg.startswith("ERROR") \
                    else "ok" if "done" in msg.lower() or "complete" in msg.lower() \
                    else "cmd" if msg.startswith("$") else None
                logbox.configure(state="normal")
                logbox.insert("end", msg + "\n", tag)
                logbox.see("end")
                logbox.configure(state="disabled")
            elif kind == "ok":
                state["flashing"] = False
                progress.stop()
                set_status("done — flashed successfully", ACCENT)
                upload_btn.configure(state="normal", bg=ACCENT)
            elif kind == "err":
                state["flashing"] = False
                progress.stop()
                set_status("failed — see log", "#dc2626")
                log("ERROR: " + msg)
                upload_btn.configure(state="normal", bg=ACCENT)
        root.after(80, drain)

    def set_status(text, color="#6b7280"):
        status_var.set(text)
        status_dot.configure(fg=color)

    # ---- header
    head = ttk.Frame(root, padding=(14, 12, 14, 0))
    head.pack(fill="x")
    ttk.Label(head, text="Arduino Zero→Hero",
              font=("", 15, "bold")).pack(side="left")
    ttk.Label(head, text="Lesson Flasher", foreground="#6b7280",
              font=("", 15)).pack(side="left", padx=(8, 0))
    ttk.Label(head, text="Pick a lesson · plug in the Uno · flash",
              foreground="#6b7280").pack(side="right")

    body = ttk.Frame(root, padding=14)
    body.pack(fill="both", expand=True)

    # ---- lesson list
    ttk.Label(body, text="LESSON", font=("", 9, "bold"),
              foreground="#6b7280").grid(row=0, column=0, sticky="w")
    lessons = ttk.Treeview(body, columns=("title", "desc"), show="headings",
                           height=8, selectmode="browse")
    lessons.heading("title", text="Project")
    lessons.heading("desc", text="What it does")
    lessons.column("title", width=235, minwidth=180, stretch=True)
    lessons.column("desc", width=320, minwidth=200, stretch=True)
    for d, t, desc in LESSONS:
        lessons.insert("", "end", iid=d,
                       values=(f"{d.split('_')[0]} · {t}", desc))
    lessons.grid(row=1, column=0, columnspan=2, sticky="ew", pady=(2, 10))
    lessons.selection_set(LESSONS[0][0])
    lscroll = ttk.Scrollbar(body, orient="vertical", command=lessons.yview)
    lessons.configure(yscrollcommand=lscroll.set)
    lscroll.grid(row=1, column=2, sticky="ns", pady=(2, 10))

    # ---- port row
    port_head = ttk.Frame(body)
    port_head.grid(row=2, column=0, columnspan=2, sticky="ew")
    ttk.Label(port_head, text="BOARD", font=("", 9, "bold"),
              foreground="#6b7280").pack(side="left")
    port_state = tk.Label(port_head, text="○ no board",
                          fg="#9ca3af", font=("", 9), bd=0)
    port_state.pack(side="left", padx=(8, 0))
    ttk.Button(port_head, text="↻ Refresh",
               command=lambda: refresh_ports(manual=True)).pack(side="right")

    port_var = tk.StringVar()
    port_box = ttk.Combobox(body, textvariable=port_var)
    port_box.grid(row=3, column=0, columnspan=2, sticky="ew", pady=(2, 10))

    port_snapshot = []

    def refresh_ports(manual=False):
        ports = list_ports()
        devices = [d for d, _ in ports]
        if devices == port_snapshot and not manual:
            return
        port_snapshot[:] = devices
        port_box["values"] = [f"{d}  —  {desc}" for d, desc in ports]
        cur = port_var.get().split("  ")[0]
        if cur in devices:                       # keep user's pick
            return
        if ports:
            port_box.current(0)
            usb = any(("ttyACM" in d or "ttyUSB" in d) for d in devices)
            port_state.configure(
                text="● board detected" if usb else "○ no USB board — showing all ports",
                fg=ACCENT if usb else "#9ca3af")
        else:
            port_var.set("")
            port_state.configure(text="○ no board — plug in the Uno",
                                 fg="#9ca3af")

    # ---- upload button + progress
    upload_btn = tk.Button(body, text="⬆  Upload to board", bg=ACCENT,
                           fg="white", activebackground="#15803d",
                           activeforeground="white", bd=0, relief="flat",
                           font=("", 12, "bold"), cursor="hand2", pady=10)
    upload_btn.grid(row=4, column=0, columnspan=2, sticky="ew")

    progress = ttk.Progressbar(body, mode="indeterminate")
    progress.grid(row=5, column=0, columnspan=2, sticky="ew", pady=(8, 10))

    # ---- log
    ttk.Label(body, text="LOG", font=("", 9, "bold"),
              foreground="#6b7280").grid(row=6, column=0, sticky="w")
    logbox = scrolledtext.ScrolledText(
        body, height=9, state="disabled", bg=LOG_BG, fg=LOG_FG,
        insertbackground=LOG_FG, bd=0, highlightthickness=0,
        font=_fixed_font())
    logbox.tag_configure("err", foreground="#f87171")
    logbox.tag_configure("ok", foreground="#4ade80")
    logbox.tag_configure("cmd", foreground="#60a5fa")
    logbox.grid(row=7, column=0, columnspan=3, sticky="nsew", pady=(2, 0))
    body.rowconfigure(7, weight=1)
    body.columnconfigure(0, weight=1)

    # ---- status bar
    bar = ttk.Frame(root)
    bar.pack(fill="x", side="bottom")
    status_dot = tk.Label(bar, text="●", fg="#6b7280", font=("", 9), bd=0)
    status_dot.pack(side="left", padx=(8, 4), pady=4)
    status_var = tk.StringVar(value="ready")
    ttk.Label(bar, textvariable=status_var, anchor="w",
              padding=(0, 4)).pack(side="left", fill="x", expand=True)

    # ---- actions
    def current_lesson():
        sel = lessons.selection()
        return sel[0] if sel else None

    def do_upload():
        lesson = current_lesson()
        if not lesson:
            messagebox.showwarning("No lesson", "Pick a lesson first.")
            return
        port = port_var.get().split("  ")[0].strip()
        if not port:
            messagebox.showwarning("No port",
                                   "Plug in the board or pick a serial port.")
            return
        hexfile = os.path.join(HEXDIR, lesson + ".hex")
        if not os.path.isfile(hexfile):
            messagebox.showerror("Missing hex", f"{hexfile} not found.")
            return
        state["flashing"] = True
        upload_btn.configure(state="disabled", bg=ACCENT_DIM)
        progress.start(12)
        set_status(f"flashing {lesson} → {port} …", "#d97706")
        log(f"── {lesson} → {port} ──")

        def worker():
            try:
                flash(port, hexfile, log)
                q.put(("ok", ""))
            except Exception as e:  # noqa: BLE001 - show any failure in GUI
                q.put(("err", str(e)))
        threading.Thread(target=worker, daemon=True).start()

    upload_btn.configure(command=do_upload)
    lessons.bind("<Double-1>", lambda _e: do_upload())
    root.bind("<Return>", lambda _e: do_upload())
    root.bind("<F5>", lambda _e: refresh_ports(manual=True))

    refresh_ports()
    drain()

    def poll_ports():                            # board just plugged in → show it
        if not state["flashing"]:
            refresh_ports()
        root.after(2000, poll_ports)
    poll_ports()

    root.mainloop()


def _fixed_font():
    try:
        import tkinter.font as tkfont
        return tkfont.nametofont("TkFixedFont")
    except Exception:
        return ("monospace", 9)


# ---------------------------------------------------------------- CLI

def run_cli(lesson, port):
    if not port:
        ports = list_ports()
        if not ports:
            sys.exit("error: no board detected on /dev/ttyACM* or /dev/ttyUSB*")
        port = ports[0][0]
    if lesson:
        matches = [d for d, _, _ in LESSONS if lesson in (d, d.split("_", 1)[1])]
        if not matches:
            sys.exit(f"error: unknown lesson '{lesson}'")
        lesson = matches[0]
    else:
        for i, (d, t, desc) in enumerate(LESSONS, 1):
            print(f"{i:2d}) {d} — {t} ({desc})")
        sel = input("flash lesson # ").strip()
        try:
            lesson = LESSONS[int(sel) - 1][0]
        except (ValueError, IndexError):
            sys.exit("invalid choice")
    hexfile = os.path.join(HEXDIR, lesson + ".hex")
    if not os.path.isfile(hexfile):
        sys.exit(f"error: {hexfile} not found")
    print(f"== {lesson} -> {port}")
    try:
        flash(port, hexfile, print)
    except Exception as e:  # noqa: BLE001
        sys.exit(f"error: {e}")
    print("done")


def main():
    ap = argparse.ArgumentParser(description="Arduino lesson flasher")
    ap.add_argument("lesson", nargs="?", help="lesson dir like 03_piano")
    ap.add_argument("--cli", action="store_true", help="run without GUI")
    ap.add_argument("--port", help="serial port, e.g. /dev/ttyACM0")
    ap.add_argument("--ontop", action="store_true", help="keep window on top")
    args = ap.parse_args()
    if args.cli or tk is None or not os.environ.get("DISPLAY"):
        run_cli(args.lesson, args.port)
    else:
        run_gui(args.ontop)


if __name__ == "__main__":
    main()
