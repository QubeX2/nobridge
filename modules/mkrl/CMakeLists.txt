add_library(mkrl STATIC
  src/mkrl.cpp
)

target_include_directories(mkrl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(mkrl PUBLIC cxx_std_23)


