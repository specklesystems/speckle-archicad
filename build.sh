#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if [[ "$(uname -s)" != "Darwin" ]]; then
  dotnet run --project "$ROOT_DIR/ci-build/Build.csproj" -- "$@"
  exit
fi

ARCHICAD_VERSION="${1:-27}"
BUILD_TYPE="${2:-Release}"

case "$ARCHICAD_VERSION" in
  27|28|29) ;;
  *)
    echo "Unsupported Archicad version: $ARCHICAD_VERSION (expected 27, 28, or 29)" >&2
    exit 2
    ;;
esac

if [[ -n "${AC_API_DEVKIT_DIR:-}" ]]; then
  DEVKIT_DIR="$AC_API_DEVKIT_DIR"
else
  DEVKIT_DIR="$("$ROOT_DIR/scripts/download_macos_devkit.sh" "$ARCHICAD_VERSION")"
fi

BUILD_DIR="$ROOT_DIR/build/mac/$ARCHICAD_VERSION"
MAC_ARCHITECTURES="${SPECKLE_MAC_ARCHITECTURES:-arm64;x86_64}"

cmake -S "$ROOT_DIR" -B "$BUILD_DIR" -G "Unix Makefiles" \
  -DAC_ADDON_LANGUAGE=INT \
  -DAC_VERSION="$ARCHICAD_VERSION" \
  -DAC_API_DEVKIT_DIR="$DEVKIT_DIR" \
  -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
  -DCMAKE_OSX_ARCHITECTURES="$MAC_ARCHITECTURES" \
  -DCMAKE_OSX_DEPLOYMENT_TARGET=12.6

cmake --build "$BUILD_DIR" --parallel

echo "Built: $BUILD_DIR/INT/$BUILD_TYPE/Speckle.bundle"
