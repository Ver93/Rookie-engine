#!/bin/bash

echo "==============================="
echo "  Building Chess Engine (Linux)"
echo "==============================="

SRC_DIR="src"
INCLUDE_DIR="src/include"
BIN_DIR="bin"
OBJ_DIR="obj"
OBJ_TEST_DIR="obj_tests"

# Create folders if missing
mkdir -p "$BIN_DIR" "$OBJ_DIR" "$OBJ_TEST_DIR"

echo "Compiling engine source files..."

# Loop through all .cpp files in src/
for f in $(find "$SRC_DIR" -name "*.cpp"); do
    FILE="$f"
    OBJ="$OBJ_DIR/$(basename "$f" .cpp).o"

    echo "[ENGINE BUILD] $(basename "$f")"
    g++ -std=c++23 -O3 -Wall -Wextra -I "$INCLUDE_DIR" -c "$FILE" -o "$OBJ"
done

echo "Linking engine..."

g++ "$OBJ_DIR"/*.o -o "$BIN_DIR"/engine

if [ $? -ne 0 ]; then
    echo "Engine build failed!"
    exit 1
fi

echo "Engine build successful!"
echo "Output: $BIN_DIR/engine"


cp bin/engine rookie-engine
