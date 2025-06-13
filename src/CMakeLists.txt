set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

file(GLOB src *.cpp)
target_sources(nobridge PRIVATE ${src})

