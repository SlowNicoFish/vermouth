#!/bin/bash
# Run the current build against a throwaway XDG config so the live library
# and settings are untouched. The temp dir is removed when the app exits.
# Може имаш ова некаде ама не видов така да бујрум!

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BIN="$SCRIPT_DIR/build/bin/vermouth"

if [ ! -x "$BIN" ]; then
    echo "Error: $BIN not found. Build first: cmake -B build && cmake --build build" >&2
    exit 1
fi

TMPCFG=$(mktemp -d -t vermouth-test-XXXXXX)
trap 'rm -rf "$TMPCFG"' EXIT

echo "Config dir: $TMPCFG"
XDG_CONFIG_HOME="$TMPCFG" XDG_DATA_HOME="$TMPCFG/data" "$BIN" "$@"
