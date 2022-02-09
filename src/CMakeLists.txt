file(GLOB_RECURSE HEADERS "${INCLUDE_DIRECTORY}/*.hpp")

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_LIST_DIR}/main.cpp")



# used for application and tests
add_library(lightgrep_lib STATIC
	${SOURCES}
)
target_include_directories(lightgrep_lib PUBLIC ${INCLUDE_DIRECTORY})
target_link_libraries(lightgrep_lib PUBLIC stdc++fs)



add_executable(lightgrep
	main.cpp
)
target_link_libraries(lightgrep PRIVATE lightgrep_lib)



add_custom_command(
	TARGET lightgrep POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_SOURCE_DIR}/build/compile_commands.json
		${CMAKE_SOURCE_DIR}/compile_commands.json)
