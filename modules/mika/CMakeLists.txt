add_library(mika STATIC
  src/mika.cpp
)

target_include_directories(mika PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(mika PUBLIC cxx_std_23)


