#include "libgit2-cpp/Error.h"

#include "git2.h"

using namespace git;

Error Error::last_error() noexcept
{
    const git_error* err = git_error_last();
    return Error{ err->message, err->klass };
}

Error::Error(const char* msg, int error_class) noexcept :
    m_msg{ msg },
    m_error_class{ error_class }
{
}

auto Error::what() const noexcept -> std::string_view
{
    return m_msg;
}


auto Error::error_class() const noexcept -> int
{
    return m_error_class;
}
