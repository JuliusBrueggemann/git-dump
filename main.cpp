#include <cstdlib>

#include "fmt/format.h"

#include "libgit2-cpp/Repository.h"

#include "git2.h"

using namespace git;

int main(int argc, char** argv) {
    git_libgit2_init();
    atexit([]{ git_libgit2_shutdown(); });

    return 0;
}
