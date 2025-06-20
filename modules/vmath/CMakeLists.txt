add_library(vmath STATIC
  src/vmath.cpp
)

target_include_directories(vmath PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(vmath PUBLIC cxx_std_23)


