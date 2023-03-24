#pragma once

#include <string>

#include "tl/expected.hpp"

#include "git2.h"

#include "Error.h"
#include "Helpers.h"

namespace git
{
    class Commit
    {
        GIT_IMPL_WRAPPER(Commit, git_commit, m_commit, git_commit_free)
    public:

        static auto from_oid(git_repository* repo, const git_oid& id) -> tl::expected<Commit, Error>;

        auto hash() const noexcept -> std::string;

    private:
        git_commit* m_commit;
    };
}
