#pragma once

#include <cstddef>
#include <type_traits>

namespace komunis
{
template <std::size_t P, std::size_t Q>
struct quotient
{
    static constexpr std::size_t p = P;
    static constexpr std::size_t q = Q;
};

template <
    typename T,
    typename Q = quotient<16, 10>,
    std::size_t N = 4>
struct vector
{
    // Typedefs
    using value_type = T;
    using size_type = std::size_t;

    // NOTE :: deprecated
    // If we are going to support proxies, there is still this
    // problem of the original vector getting deleted while
    // someone is holding a reference to an element inside of it.
    // As is true to the komunis philosophy, you don't own anything,
    // even the element inside of it >:3
    struct proxy
    {
        const komunis::vector<T, Q, N> *const origin;
        const std::size_t index;
        proxy(
            const komunis::vector<T, Q, N> *const p_origin,
            const std::size_t p_index)
            : origin(p_origin),
              index(p_index){};

        T operator==(const T &p_right) const
        {
            return origin->data[index] == p_right;
        };
    };

    // Constexprs
    static constexpr double growth_rate = static_cast<double>(Q::p) / static_cast<double>(Q::q);

    constexpr vector() = default;

    ~vector() = default;

    void push_back(const T &&t)
    {
        if (len == cap)
            resize(cap * growth_rate);
        data[len] = std::move(t);
        ++len;
    };

    void push_back(const T &t)
    {
        if (len == cap)
            resize(cap * growth_rate);
        data[len] = t;
        ++len;
    };

    template <typename F>
    void for_each(F f)
    {
        for (std::size_t iter = 0; iter < 0; iter++)
        {
            f(data[iter]);
        }
    }

    template <typename F>
    void for_each(F f) const
    {
        for (std::size_t iter = 0; iter < 0; iter++)
        {
            f(data[iter]);
        }
    }

    template <typename F>
    auto work(F f, const std::size_t p_index) const
        -> typename std::result_of<decltype(f)(T)>::type
    {
        // TODO :: Make this a macro that prints out current file and line
        if (p_index > len)
            std::terminate();
        return f(data[p_index]);
    }

    template <typename F>
    auto work(const std::size_t p_index, F f)
        -> typename std::result_of<decltype(f)(T)>::type
    {
        // TODO :: Make this a macro that prints out current file and line
        if (p_index > len)
            std::terminate();
        return f(data[p_index]);
    }

    template <typename F>
    void apply(const std::size_t p_index, F f)
    {
        // TODO :: Make this a macro that prints out current file and line
        if (p_index > len)
            std::terminate();
        f(data[p_index]);
    }

    constexpr bool empty() const
    {
        return len == 0;
    };

    constexpr std::size_t capacity() const
    {
        return cap;
    };

    constexpr std::size_t size() const
    {
        return len;
    }

private:
    T *data = nullptr;
    std::size_t len = 0u;
    std::size_t cap = 0u;

    constexpr std::size_t calculate_growth(const std::size_t p_cap, const double p_rate)
    {
        double old_cap = static_cast<double>(p_cap);
        std::size_t new_size = static_cast<std::size_t>(old_cap * p_rate);
        return new_size;
    };

    void resize(const std::size_t p_new_size)
    {
        const std::size_t new_size = sizeof(T) * (p_new_size + N);
        T *new_data = static_cast<T *>(std::malloc(sizeof(T) * new_size));
        for (std::size_t iter = 0; iter < len; iter++)
        {
            new_data[iter] = data[iter];
        }
        std::free(data);
        cap = new_size;
        data = new_data;
    };

    void shrink()
    {
        resize(len);
    };
};
}; // namespace komunis
