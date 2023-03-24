#include "libgit2-cpp/Repository.h"

#include <cassert>

using namespace git;

auto Repository::open(const char* path) noexcept -> tl::expected<Repository, Error>
{
    assert(path != nullptr);
    git_repository* repo = nullptr;
    int error = git_repository_open(&repo, path);
    if (error < 0)
    {
        return tl::make_unexpected(Error::last_error());
    }

    return Repository{ repo };
}

auto Repository::head() const noexcept -> tl::expected<Commit, Error>
{
    git_oid oid{};
    int error = git_reference_name_to_id(&oid, m_repo, "HEAD");
    if (error < 0)
    {
        return tl::make_unexpected(Error::last_error());
    }

    return Commit::from_oid(*this, oid);
}

auto Repository::is_dirty() const noexcept -> tl::expected<bool, Error>
{
    // TODO Write RAII wrappers around these types
    // TODO Error handling
    git_object* obj = nullptr;
    int error = git_revparse_single(&obj, m_repo, "HEAD^{tree}");

    git_tree* tree = nullptr;
    error = git_tree_lookup(&tree, m_repo, git_object_id(obj));

    git_diff* diff = nullptr;
    error = git_diff_tree_to_workdir_with_index(&diff, m_repo, tree, nullptr);

    auto num_deltas = git_diff_num_deltas(diff);

    git_diff_free(diff);
    git_tree_free(tree);
    git_object_free(obj);

    return num_deltas > 0;
}
