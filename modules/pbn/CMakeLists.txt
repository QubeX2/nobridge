add_library(pbn STATIC
  src/reader.cpp
  src/parser.cpp
  src/pbn.cpp
)

target_link_libraries(pbn
  PRIVATE 
  mkrl
)

target_include_directories(pbn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(pbn PUBLIC cxx_std_23)


