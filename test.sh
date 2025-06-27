#!/bin/bash

set -e

BUILD_DIR="build-tests"

# === CHECK FOR BUILD DIRECTORY ===
if [ ! -d "$BUILD_DIR" ]; then
  echo "❌ No build directory found. Run ./build.sh first."
  exit 1
fi

cd $BUILD_DIR

# === OPTIONAL: Build again before testing ===
echo "🔄 Building (to ensure tests are up-to-date)..."
ninja

args=("--output-on-failure" "--verbose")

if [ -n "$1" ]; then
  args+=("-R" "$1")
fi

# === RUN TESTS ===
echo "🧪 Running tests with CTest..."
ctest "${args[@]}" 

echo "✅ All tests completed."
