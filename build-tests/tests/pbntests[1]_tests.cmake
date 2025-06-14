add_test([=[PbnTest.DefaultTest]=]  /Users/mikael/Projects/cpp/nobridge/build-tests/tests/pbntests [==[--gtest_filter=PbnTest.DefaultTest]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PbnTest.DefaultTest]=]  PROPERTIES WORKING_DIRECTORY /Users/mikael/Projects/cpp/nobridge/build-tests/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  pbntests_TESTS PbnTest.DefaultTest)
