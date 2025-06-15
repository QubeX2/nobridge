add_library(storage STATIC
  src/handt.cpp
)

target_include_directories(storage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(storage PUBLIC cxx_std_23)


