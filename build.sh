#!/bin/bash

set -e

echo "===================================="
echo "  Building Chess Engine (Linux)"
echo "===================================="

SRC_DIR="src"
INCLUDE_DIR="src/include"
BIN_DIR="bin"
OBJ_DEBUG="obj_debug"
OBJ_RELEASE="obj_release"

# Create folders if missing
mkdir -p "$BIN_DIR" "$OBJ_DEBUG" "$OBJ_RELEASE"

# Choose build type
if [ -z "$1" ]; then
    echo "Usage: ./build.sh [debug|release]"
    exit 1
fi

if [ "$1" = "debug" ]; then
    MODE="debug"
    CFLAGS="-std=c++23 -O0 -g -Wall -Wextra -I $INCLUDE_DIR"
    OBJ_DIR="$OBJ_DEBUG"
    OUT_FILE="$BIN_DIR/engine_debug"
elif [ "$1" = "release" ]; then
    MODE="release"
    CFLAGS="-std=c++23 -O3 -march=native -flto -DNDEBUG -Wall -Wextra -I $INCLUDE_DIR"
    OBJ_DIR="$OBJ_RELEASE"
    OUT_FILE="$BIN_DIR/engine"
else
    echo "Invalid mode. Use: debug or release"
    exit 1
fi

echo "===================================="
echo "  Mode: $MODE"
echo "===================================="

# Compile all .cpp files
for f in $(find "$SRC_DIR" -name "*.cpp"); do
    OBJ="$OBJ_DIR/$(basename "$f" .cpp).o"
    echo "[COMPILING] $(basename "$f")"
    g++ $CFLAGS -c "$f" -o "$OBJ"
done

# Linking
echo "[LINKING] $OUT_FILE"
g++ $CFLAGS "$OBJ_DIR"/*.o -o "$OUT_FILE"

echo "===================================="
echo "  Build successful!"
echo "  Output: $OUT_FILE"
echo "===================================="
