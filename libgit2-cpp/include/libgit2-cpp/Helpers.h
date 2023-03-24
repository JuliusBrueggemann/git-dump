#pragma once

#include <utility>

#define GIT_NO_COPY(class_name)                                                                                        \
    class_name(const class_name&) = delete;                                                                            \
    class_name& operator=(const class_name&) = delete;

#define GIT_IMPL_MOVE(class_name, ptr)                                                                                 \
    class_name(class_name&& other) noexcept :                                                                          \
        ptr{ std::exchange(other.ptr, nullptr) }                                                                       \
    {                                                                                                                  \
    }                                                                                                                  \
                                                                                                                       \
    class_name& operator=(class_name&& other) noexcept                                                                 \
    {                                                                                                                  \
        swap(*this, other);                                                                                            \
        return *this;                                                                                                  \
    }                                                                                                                  \
                                                                                                                       \
    friend void swap(class_name& l, class_name& r) noexcept                                                            \
    {                                                                                                                  \
        std::swap(l.ptr, r.ptr);                                                                                       \
    }

#define GIT_IMPL_DTOR(class_name, ptr, free_func)                                                                      \
    ~class_name() noexcept                                                                                             \
    {                                                                                                                  \
        if (ptr != nullptr)                                                                                            \
        {                                                                                                              \
            free_func(ptr);                                                                                            \
        }                                                                                                              \
    }

#define GIT_IMPL_CONVERSION(type, ptr)                                                                                 \
    operator type*() const noexcept                                                                                    \
    {                                                                                                                  \
        return ptr;                                                                                                    \
    }

#define GIT_IMPL_CTOR(class_name, type, ptr)                                                                           \
    explicit class_name(type* value) noexcept :                                                                        \
        ptr{ value }                                                                                                   \
    {                                                                                                                  \
    }

#define GIT_IMPL_WRAPPER(class_name, type, ptr, free_func)                                                             \
public:                                                                                                                \
    GIT_NO_COPY(class_name)                                                                                            \
    GIT_IMPL_MOVE(class_name, ptr)                                                                                     \
    GIT_IMPL_DTOR(class_name, ptr, free_func)                                                                          \
    GIT_IMPL_CONVERSION(type, ptr)                                                                                     \
private:                                                                                                               \
    GIT_IMPL_CTOR(class_name, type, ptr)
