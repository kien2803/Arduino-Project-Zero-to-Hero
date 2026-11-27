#!/usr/bin/env bash
# build.sh — prebuild build/<lesson>.hex for every sketch.
# These let flash.sh upload without PlatformIO/arduino-cli installed
# (only avrdude needed on the flashing machine).
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p build

if command -v pio >/dev/null; then
  backend=pio
elif command -v arduino-cli >/dev/null; then
  backend=arduino-cli
else
  echo "error: need platformio (pip install --user platformio) or arduino-cli" >&2
  exit 1
fi
echo "backend: $backend"

for ino in */*.ino; do
  dir=$(dirname "$ino"); lesson=$(basename "$dir")
  tmp=$(mktemp -d)
  echo "== $lesson"
  case $backend in
    pio)
      mkdir -p "$tmp/src"
      cp "$ino" "$tmp/src/"
      find "$dir" -maxdepth 1 \( -name '*.h' -o -name '*.hpp' -o -name '*.cpp' \) \
        -exec cp {} "$tmp/src/" \;
      pio ci -c platformio.ini --build-dir "$tmp/out" --keep-build-dir "$tmp/src" >/dev/null
      cp "$(find "$tmp/out" -name firmware.hex | head -1)" "build/$lesson.hex"
      ;;
    arduino-cli)
      # arduino-cli requires <folder>/<folder>.ino — sketch names here
      # don't match their dirs, so compile a renamed copy in a temp dir
      sk="$tmp/$lesson"; mkdir -p "$sk"
      cp "$ino" "$sk/$lesson.ino"
      arduino-cli compile --fqbn arduino:avr:uno --output-dir "$tmp/out" "$sk" >/dev/null
      cp "$tmp/out"/*.hex "build/$lesson.hex"
      ;;
  esac
  rm -rf "$tmp"
done
echo "done → build/*.hex"
