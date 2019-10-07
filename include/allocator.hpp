#pragma once

namespace ktl
{
template <class T>
class allocator
{
public:
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    using value_type = T;

    allocator() = default;
    allocator(const allocator &) = default;

    pointer allocate(size_type n, const void * = nullptr)
    {
        T *t = static_cast<T *>(std::malloc(n * sizeof(T)));
        return t;
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

    allocator<T> &operator=(const allocator &)
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

    size_type max_size() const { return size_t(-1); }

    template <class U>
    struct rebind
    {
        using other = allocator<U>;
    };
};
}; // namespace ktl