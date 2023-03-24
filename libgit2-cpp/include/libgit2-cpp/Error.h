#pragma once

#include <string>
#include <string_view>

namespace git
{
    class Error
    {
    public:
        static Error last_error() noexcept;

        auto what() const noexcept -> std::string_view;
        auto error_class() const noexcept -> int;

    private:
        std::string m_msg;
        int m_error_class;

        Error(const char* msg, int error_class) noexcept;
    };
} // namespace git
