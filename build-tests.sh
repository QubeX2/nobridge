#!/bin/bash

set -e

# === CONFIG ===
C_COMPILER="/usr/bin/clang"
CXX_COMPILER="/usr/bin/clang++"  # or replace with Homebrew LLVM if needed
BUILD_DIR="build-tests"

# === CLEAN ===
echo "🧹 Cleaning previous build and CMake cache..."
rm -rf ${BUILD_DIR} CMakeCache.txt CMakeFiles cmake_install.cmake Makefile compile_commands.json

# === CREATE BUILD DIR ===
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

# === CMAKE CONFIGURE ===
echo "⚙️  Configuring project with Ninja and Clang..."
cmake -G Ninja \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_C_COMPILER=${C_COMPILER} \
  -DCMAKE_CXX_COMPILER=${CXX_COMPILER} \
  -DENABLE_TESTING=ON \
  ..

# === BUILD ===
echo "🔨 Building project + tests..."
ninja

# === LINK COMPILE_COMMANDS ===
echo "🔗 Linking compile_commands.json to project root..."
cd ..
ln -sf ${BUILD_DIR}/compile_commands.json .


# === COPY TEST FILES ===
echo "Copying test files..."
cp -r tests/files ${BUILD_DIR}/tests/
echo "✅ Done! Test build complete."


