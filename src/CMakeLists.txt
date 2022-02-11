file(GLOB_RECURSE HEADERS "${INCLUDE_DIRECTORY}/*.hpp")

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_LIST_DIR}/main.cpp")



# used for application and tests
add_library(flexgrep_lib STATIC
	${SOURCES}
)
target_include_directories(flexgrep_lib PUBLIC ${INCLUDE_DIRECTORY})
# target_link_libraries(flexgrep_lib PUBLIC stdc++fs)



add_executable(flexgrep
	main.cpp
)
target_link_libraries(flexgrep PRIVATE flexgrep_lib)
