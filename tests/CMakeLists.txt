add_executable(pbntests test_pbn.cpp)
target_link_libraries(pbntests gtest_main pbnlib)

include(GoogleTest)

gtest_discover_tests(pbntests)
