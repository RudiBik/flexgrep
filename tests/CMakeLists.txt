project(tests)


# Download GTest dependency automatically 
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
find_package(Threads REQUIRED)



add_executable(tests
	testmain.cpp
)
target_link_libraries(tests PRIVATE flexgrep_lib)

target_include_directories(tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(tests PRIVATE gtest_main)
target_link_libraries(tests PRIVATE Threads::Threads)



#add_test(AllTestsIntests tests)
