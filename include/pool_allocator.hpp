#pragma once

#include <mutex>

namespace akarin
{
template <class T>
struct pool_allocator
{
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    using value_type = T;

    pool_allocator() = default;
    pool_allocator(const pool_allocator &) = default;

    pointer allocate(size_type n, const void * = nullptr)
    {
        T *t = static_cast<T *>(std::malloc(n * sizeof(T)));
        if (idx == cap)
        {
        }
        return (data + (idx++));
    }

    void deallocate(void *p, size_type)
    {
        std::free(p);
    };

    pointer address(reference x) const
    {
        return &x;
    };

    const_pointer address(const_reference x) const
    {
        return &x;
    };

    pool_allocator<T> &operator=(const pool_allocator &)
    {
        return *this;
    };

    void construct(pointer p, const T &val)
    {
        new ((T *)p) T(val);
    };

    void destroy(pointer p)
    {
        p->~T();
    };

    template <class U>
    struct rebind
    {
        using other = pool_allocator<U>;
    };

private:
    static pointer data;
    static std::size_t idx;
    static std::size_t cap;
    static vector<std::size_t> unused;
};

template <typename T>
typename pool_allocator<T>::pointer pool_allocator<T>::data = nullptr;

template <typename T>
typename std::size_t pool_allocator<T>::idx = 0;

template <typename T>
typename std::size_t pool_allocator<T>::cap = 0;
}; // namespace akarin
