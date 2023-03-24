add_library(libgit2-cpp STATIC
        src/Repository.cpp include/libgit2-cpp/Repository.h
        src/Error.cpp include/libgit2-cpp/Error.h
        src/Commit.cpp include/libgit2-cpp/Commit.h
        include/libgit2-cpp/Helpers.h)

target_include_directories(libgit2-cpp PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(libgit2-cpp PUBLIC unofficial::git2::git2 tl::expected tl::optional PRIVATE fmt::fmt)
