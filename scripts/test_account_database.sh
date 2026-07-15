#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$(mktemp -d "${TMPDIR:-/tmp}/speckle-account-database-test.XXXXXX")"
TEST_HOME="$(mktemp -d "${TMPDIR:-/tmp}/speckle-account-database-home.XXXXXX")"
trap 'rm -rf "$BUILD_DIR" "$TEST_HOME"' EXIT

clang -std=c11 \
  -I "$ROOT_DIR/Libs/sqlite/include" \
  -c "$ROOT_DIR/Libs/sqlite/src/sqlite3.c" \
  -o "$BUILD_DIR/sqlite3.o"

clang++ -std=c++20 \
  -I "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Connector" \
  -I "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Utils" \
  -I "$ROOT_DIR/Libs/json/include" \
  -I "$ROOT_DIR/Libs/sqlite/include" \
  "$ROOT_DIR/tests/AccountDatabaseTests.cpp" \
  "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Connector/AccountDatabase.cpp" \
  "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Utils/PlatformPaths.cpp" \
  "$BUILD_DIR/sqlite3.o" \
  -o "$BUILD_DIR/account_database_tests"

HOME="$TEST_HOME" "$BUILD_DIR/account_database_tests"
