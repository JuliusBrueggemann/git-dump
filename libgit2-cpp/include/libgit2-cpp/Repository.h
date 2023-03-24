#pragma once

#include "tl/expected.hpp"

#include "git2.h"

#include "Commit.h"
#include "Error.h"
#include "Helpers.h"

namespace git
{
    class Repository
    {
        GIT_IMPL_WRAPPER(Repository, git_repository, m_repo, git_repository_free)
    public:

        static auto open(const char* path) noexcept -> tl::expected<Repository, Error>;

        /// @brief Returns the currently checked out commit in this repository (as determined
        ///        by the HEAD ref)
        auto head() const noexcept -> tl::expected<Commit, Error>;

        /// @brief Returns whether there are uncommitted changes.
        ///
        /// @warning This method only checks if there are changes to existing file. Essentially,
        /// it does "git diff HEAD" and checks if the diff is empty. This means that adding new, untracked
        /// files does not dirty the repository.
        auto is_dirty() const noexcept -> tl::expected<bool, Error>;

    private:
        git_repository* m_repo;
    };
}
