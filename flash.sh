#!/usr/bin/env bash
# flash.sh — pick a lesson and flash it to an Arduino Uno over USB.
#
#   ./flash.sh                 interactive menu
#   ./flash.sh 03_piano        flash directly, no menu
#   PORT=/dev/ttyUSB0 ./flash.sh
#
# Backend: compiles with PlatformIO (pio ci) when installed, otherwise
# flashes the prebuilt build/<lesson>.hex (generate with ./build.sh).
set -euo pipefail
cd "$(dirname "$0")"

MCU=atmega328p; PROGRAMMER=arduino; BAUD=115200; HEXDIR=build

die() { echo "error: $*" >&2; exit 1; }

# avrdude: system install, or the copy bundled inside arduino-cli's toolchain
AVRDUDE=$(command -v avrdude \
  || ls ~/.arduino15/packages/arduino/tools/avrdude/*/bin/avrdude 2>/dev/null | head -1 \
  || true)
[ -n "$AVRDUDE" ] || die "avrdude not found — install it: sudo dnf install avrdude"

PORT=${PORT:-}
[ -n "$PORT" ] || for p in /dev/ttyACM* /dev/ttyUSB*; do
  [ -e "$p" ] && { PORT=$p; break; }
done
[ -n "$PORT" ] || die "no board on /dev/ttyACM* or /dev/ttyUSB* — plug in the Uno (or set PORT=...)"

# --- pick a lesson ---
mapfile -t sketches < <(printf '%s\n' */*.ino | sort)
[ ${#sketches[@]} -gt 0 ] || die "no *.ino sketches found"

if [ $# -ge 1 ]; then
  if [ -f "$1" ]; then
    choice=$1
  elif [ -d "$1" ]; then
    choice=$(printf '%s\n' "${sketches[@]}" | grep "^$1/" | head -1 || true)
  fi
  [ -f "${choice:-}" ] || die "unknown lesson '$1' — expected a folder like 03_piano or a .ino path"
elif command -v fzf >/dev/null && [ -t 0 ] && [ -t 1 ]; then
  choice=$(printf '%s\n' "${sketches[@]}" | fzf --prompt='flash > ' --height=~50%) || exit 0
else
  echo "Select a lesson to flash:"
  select choice in "${sketches[@]}"; do
    [ -n "$choice" ] && break
    echo "invalid choice" >&2
  done
fi

lesson=$(basename "$(dirname "$choice")")
echo "== $choice  ->  $PORT"

# --- compile with PlatformIO, or reuse a prebuilt hex ---
if command -v pio >/dev/null; then
  tmp=$(mktemp -d); trap 'rm -rf "$tmp"' EXIT
  mkdir -p "$tmp/src"
  cp "$choice" "$tmp/src/"
  find "$(dirname "$choice")" -maxdepth 1 \( -name '*.h' -o -name '*.hpp' -o -name '*.cpp' \) \
    -exec cp {} "$tmp/src/" \;
  echo "compiling with PlatformIO..."
  if ! pio ci -c platformio.ini --build-dir "$tmp/out" --keep-build-dir "$tmp/src" >"$tmp/pio.log" 2>&1; then
    cat "$tmp/pio.log" >&2
    die "compile failed"
  fi
  hex=$(find "$tmp/out" -name firmware.hex | head -1)
  [ -f "$hex" ] || die "compile produced no .hex"
  mkdir -p "$HEXDIR"
  cp "$hex" "$HEXDIR/$lesson.hex"
else
  hex="$HEXDIR/$lesson.hex"
  [ -f "$hex" ] || die "no prebuilt $hex and platformio is not installed.
  either:  python3 -m pip install --user platformio
  or run:  ./build.sh"
  echo "using prebuilt $hex"
fi

"$AVRDUDE" -p "$MCU" -c "$PROGRAMMER" -P "$PORT" -b "$BAUD" -D -U "flash:w:$hex:i"
echo "done — $choice flashed."
