#include <cstdlib>
#include <string_view>

#include "fmt/format.h"

#include "libgit2-cpp/Repository.h"

using namespace git;

static constexpr std::string_view USAGE =
    R"(USAGE: git-dump [Options...] Repository

OPTIONS:
    -o File                     Specifies the name of the output file. By default, output is printed to stdout.
    -h --hash                   Output the hash of the HEAD.
    -d --dirty                  Output whether the repository has uncommitted changes.
    -s --summary                Output the summary of the current commit. The summary is the first paragraph of the commit message.
)";

const char* repository = nullptr;
FILE* output = stdout;
bool output_hash = false;
bool output_dirty = false;
bool output_summary = false;

void parse_cmd_line(int argc, char** argv);

int main(int argc, char** argv)
{
    git_libgit2_init();
    atexit([] { git_libgit2_shutdown(); });

    parse_cmd_line(argc, argv);

    auto repo = Repository::open(repository)
                    .or_else([](const Error& e) {
                        fmt::print(stderr, "Failed to open repository \"{}\": {}\n", repository, e.what());
                        std::exit(e.error_class());
                    })
                    .value();

    if (output_hash)
    {
        auto hash = repo.head()
                        .map([](const Commit& c) { return c.hash(); })
                        .or_else([](const Error& e) {
                            fmt::print(stderr, "Failed to get commit hash: {}\n", e.what());
                            std::exit(e.error_class());
                        })
                        .value();
        fmt::print(output, "static constexpr char GIT_HEAD[] = \"{}\";\n", hash);
    }

    if (output_dirty)
    {
        bool dirty = repo.is_dirty()
                         .or_else([](const Error& e) {
                             fmt::print(stderr, "Failed to check if repo is dirty: {}\n", e.what());
                             std::exit(e.error_class());
                         })
                         .value();
        fmt::print(output, "static constexpr bool GIT_IS_DIRTY = {};\n", dirty);
    }

    if (output_summary)
    {
        auto summary = repo.head()
                           .map([](const Commit& c) { return c.summary(); })
                           .or_else([](const Error& e) {
                               fmt::print(stderr, "Failed to get commit summary: {}\n", e.what());
                               std::exit(e.error_class());
                           })
                           .value();
        fmt::print(output, "static constexpr char GIT_HEAD_SUMMARY[] = \"{}\";\n", summary);
    }

    if (output != stdout)
        fclose(output);

    return 0;
}

void parse_cmd_line(int argc, char** argv)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string_view arg = argv[i];
        if (arg == "-o")
        {
            ++i;
            if (i == argc)
            {
                fmt::print(stderr, USAGE);
                std::exit(1);
            }

            output = fopen(argv[i], "w");
        }
        else if (arg == "-h" || arg == "--hash")
        {
            output_hash = true;
        }
        else if (arg == "-d" || arg == "--dirty")
        {
            output_dirty = true;
        }
        else if (arg == "-s" || arg == "--summary")
        {
            output_summary = true;
        }
        else
        {
            repository = arg.data();
        }
    }

    if (repository == nullptr)
    {
        fmt::print(stderr, USAGE);
        std::exit(1);
    }
}
