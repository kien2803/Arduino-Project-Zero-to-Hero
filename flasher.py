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
    ("05_thermometer",      "Room Thermometer",         "NTC sensor + LCD temperature display"),
    ("06_anti_theft_alarm", "Anti-Theft Alarm",         "Vibration sensor + buzzer alarm"),
    ("07_remote_lamp",      "Remote Controlled Lamp",   "IR remote + relay switching"),
    ("08_password_lock",    "Password Lock",            "4x4 keypad + 4-digit password"),
    ("09_servo_barrier",    "Servo Barrier Gate",       "SG90 servo parking barrier"),
    ("10_rfid_access",      "RFID Access Control",      "RC522 card reader + UID check"),
    ("11_smart_door_lock",  "Smart Door Lock",          "RFID + keypad + LCD + servo (flagship)"),
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
    """Return [(device, description)]."""
    try:
        from serial.tools import list_ports as lp
        return [(p.device, p.description or p.device) for p in lp.comports()]
    except ImportError:
        devs = sorted(glob.glob("/dev/ttyACM*") + glob.glob("/dev/ttyUSB*"))
        return [(d, d) for d in devs]


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

def run_gui():
    root = tk.Tk()
    root.title("Arduino Zero→Hero — Lesson Flasher")
    root.minsize(520, 480)
    q = queue.Queue()

    def log(msg):
        q.put(("log", msg))

    def drain():
        while True:
            try:
                kind, msg = q.get_nowait()
            except queue.Empty:
                break
            if kind == "log":
                logbox.configure(state="normal")
                logbox.insert("end", msg + "\n")
                logbox.see("end")
                logbox.configure(state="disabled")
            elif kind == "ok":
                status_var.set("done — flashed successfully")
                upload_btn.configure(state="normal")
            elif kind == "err":
                status_var.set("failed — see log")
                log("ERROR: " + msg)
                upload_btn.configure(state="normal")
        root.after(80, drain)

    top = ttk.Frame(root, padding=12)
    top.pack(fill="both", expand=True)

    ttk.Label(top, text="Lesson", font=("", 11, "bold")).grid(row=0, column=0, sticky="w")
    lesson_var = tk.StringVar()
    lesson_box = ttk.Combobox(top, textvariable=lesson_var, state="readonly",
                              values=[f"{d} — {t}" for d, t, _ in LESSONS])
    lesson_box.grid(row=1, column=0, columnspan=2, sticky="ew", pady=(2, 8))
    lesson_box.current(0)

    desc_var = tk.StringVar()
    ttk.Label(top, textvariable=desc_var, foreground="#555").grid(
        row=2, column=0, columnspan=2, sticky="w")

    def on_pick(_=None):
        i = lesson_box.current()
        desc_var.set(LESSONS[i][2])
        hexes = glob.glob(os.path.join(HEXDIR, LESSONS[i][0] + ".hex"))
        status_var.set("" if hexes else "no prebuilt hex for this lesson")
    lesson_box.bind("<<ComboboxSelected>>", on_pick)

    ttk.Label(top, text="Board port", font=("", 11, "bold")).grid(
        row=3, column=0, sticky="w", pady=(8, 0))
    port_var = tk.StringVar()
    port_box = ttk.Combobox(top, textvariable=port_var)
    port_box.grid(row=4, column=0, sticky="ew", pady=(2, 8))

    def refresh_ports():
        ports = list_ports()
        port_box["values"] = [f"{d}  ({desc})" for d, desc in ports]
        if ports:
            port_box.current(0)
        else:
            port_var.set("")
            status_var.set("no board detected — plug in the Uno, then Refresh")
    ttk.Button(top, text="↻ Refresh", command=refresh_ports).grid(
        row=4, column=1, sticky="e", padx=(8, 0))

    upload_btn = ttk.Button(top, text="⬆  Upload to board")
    upload_btn.grid(row=5, column=0, columnspan=2, sticky="ew", ipady=6)

    logbox = scrolledtext.ScrolledText(top, height=12, state="disabled",
                                     font=("monospace", 9))
    logbox.grid(row=6, column=0, columnspan=2, sticky="nsew", pady=(10, 4))
    top.rowconfigure(6, weight=1)
    top.columnconfigure(0, weight=1)

    status_var = tk.StringVar(value="ready")
    ttk.Label(root, textvariable=status_var, relief="sunken",
              anchor="w", padding=4).pack(fill="x", side="bottom")

    def do_upload():
        i = lesson_box.current()
        if i < 0:
            messagebox.showwarning("No lesson", "Pick a lesson first.")
            return
        port = port_var.get().split()[0]
        if not port:
            messagebox.showwarning("No port", "Pick the board's serial port.")
            return
        hexfile = os.path.join(HEXDIR, LESSONS[i][0] + ".hex")
        if not os.path.isfile(hexfile):
            messagebox.showerror("Missing hex", f"{hexfile} not found.")
            return
        upload_btn.configure(state="disabled")
        status_var.set(f"flashing {LESSONS[i][0]} → {port} …")

        def worker():
            try:
                flash(port, hexfile, log)
                q.put(("ok", ""))
            except Exception as e:  # noqa: BLE001 - show any failure in GUI
                q.put(("err", str(e)))
        threading.Thread(target=worker, daemon=True).start()

    upload_btn.configure(command=do_upload)
    refresh_ports()
    on_pick()
    drain()
    root.mainloop()


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
    args = ap.parse_args()
    if args.cli or tk is None or not os.environ.get("DISPLAY"):
        run_cli(args.lesson, args.port)
    else:
        run_gui()


if __name__ == "__main__":
    main()
