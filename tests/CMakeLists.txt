add_executable(test_pbn test_pbn.cpp)
target_link_libraries(test_pbn PRIVATE GTest::gtest GTest::gtest_main pbn mkrl)

add_executable(test_engine test_engine.cpp)
target_link_libraries(test_engine PRIVATE GTest::gtest GTest::gtest_main engine mkrl)

add_executable(test_storage test_storage.cpp)
target_link_libraries(test_storage PRIVATE GTest::gtest GTest::gtest_main mkrl)

include(GoogleTest)

gtest_discover_tests(test_engine)
gtest_discover_tests(test_pbn)
gtest_discover_tests(test_storage)
