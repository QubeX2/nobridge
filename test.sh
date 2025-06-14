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

# === RUN TESTS ===
echo "🧪 Running tests with CTest..."
ctest --output-on-failure --verbose

echo "✅ All tests completed."
