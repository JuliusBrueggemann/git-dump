cmake_minimum_required(VERSION 3.25)
project(git_dump)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt CONFIG REQUIRED)
find_package(unofficial-git2 CONFIG REQUIRED)
find_package(tl-optional CONFIG REQUIRED)
find_package(tl-expected CONFIG REQUIRED)

add_subdirectory(libgit2-cpp)

add_executable(git_dump main.cpp)
target_link_libraries(git_dump PUBLIC libgit2-cpp)

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
	install(TARGETS git_dump RUNTIME_DEPENDENCIES PRE_EXCLUDE_REGEXES "^api-" "^ext-" POST_EXCLUDE_REGEXES "system32/.*")
else()
	install(TARGETS git_dump)
endif()
