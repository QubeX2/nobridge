add_library(pbnlib STATIC
  src/reader.cpp
  src/writer.cpp
)

target_include_directories(pbnlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(pbnlib PUBLIC cxx_std_23)


