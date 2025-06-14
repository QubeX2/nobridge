cmake_minimum_required(VERSION 3.14)

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

# Testing
option(ENABLE_TESTING, "Build tests" ON)
if(ENABLE_TESTING)
  include(FetchContent)

  cmake_policy(SET CMP0135 NEW)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )

  FetchContent_MakeAvailable(googletest)
  enable_testing()
  add_subdirectory(tests)  # You'll create this directory
endif()
