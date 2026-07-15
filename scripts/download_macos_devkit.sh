#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ARCHICAD_VERSION="${1:-}"

case "$ARCHICAD_VERSION" in
  27) DEVKIT_RELEASE="27.6003" ;;
  28) DEVKIT_RELEASE="28.4001" ;;
  29) DEVKIT_RELEASE="29.3100" ;;
  *)
    echo "Usage: $0 <27|28|29>" >&2
    exit 2
    ;;
esac

CACHE_ROOT="${SPECKLE_DEVKIT_CACHE:-$ROOT_DIR/.cache/archicad-devkits}"
DEVKIT_DIR="$CACHE_ROOT/$DEVKIT_RELEASE"
ARCHIVE="$CACHE_ROOT/API.Development.Kit.MAC.$DEVKIT_RELEASE.zip"

if [[ ! -f "$DEVKIT_DIR/Support/Lib/libACAP_STAT.a" ]]; then
  mkdir -p "$CACHE_ROOT"
  if [[ ! -f "$ARCHIVE" ]]; then
    curl --fail --location --retry 3 \
      "https://github.com/GRAPHISOFT/archicad-api-devkit/releases/download/$DEVKIT_RELEASE/API.Development.Kit.MAC.$DEVKIT_RELEASE.zip" \
      --output "$ARCHIVE"
  fi

  TEMP_DIR="$(mktemp -d "${TMPDIR:-/tmp}/speckle-archicad-devkit.XXXXXX")"
  trap 'rm -rf "$TEMP_DIR"' EXIT
  unzip -q "$ARCHIVE" 'Support/*' -d "$TEMP_DIR"
  mkdir -p "$DEVKIT_DIR"
  mv "$TEMP_DIR/Support" "$DEVKIT_DIR/Support"
fi

echo "$DEVKIT_DIR"
