#include "libgit2-cpp/Commit.h"

#include <array>

using namespace git;

auto Commit::from_oid(git_repository* repo, const git_oid& id) -> tl::expected<Commit, Error>
{
    git_commit* commit = nullptr;
    int error = git_commit_lookup(&commit, repo, &id);
    if (error < 0)
    {
        return tl::make_unexpected(Error::last_error());
    }

    return Commit{ commit };
}

auto Commit::hash() const noexcept -> std::string
{
    const git_oid* id = git_commit_id(m_commit);
    std::array<char, GIT_OID_HEXSZ + 1> buffer;
    char* result = git_oid_tostr(buffer.data(), buffer.size(), id);
    return result;
}
