project(tests)


enable_testing()
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)



add_executable(tests
	testmain.cpp
)
target_link_libraries(tests PRIVATE lightgrep_lib)

target_include_directories(tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(tests PRIVATE GTest::GTest)
target_link_libraries(tests PRIVATE Threads::Threads)



#add_test(AllTestsIntests tests)
