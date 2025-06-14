cmake_minimum_required(VERSION 4.0)

project (nobridge
  VERSION 0.1.0
  DESCRIPTION "Bridge Robot"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(modules/engine)
add_subdirectory(modules/pbnlib)
add_subdirectory(modules/storage)
add_subdirectory(apps/CLI)
