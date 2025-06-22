add_library(adapter STATIC
  src/adapter.cpp
)

target_link_libraries(adapter
  PRIVATE 
  mika
  engine
)

target_include_directories(adapter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(adapter PUBLIC cxx_std_23)


