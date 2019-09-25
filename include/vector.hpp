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

    // Constexprs
    static constexpr double growth_rate = static_cast<double>(Q::p) / static_cast<double>(Q::q);

    constexpr vector() = default;

    ~vector()
    {
        std::free(data);
    };

    vector &operator=(const vector &p_vec)
    {
        if (this == &p_vec)
            return *this; // no need to copy
        clear();
        p_vec.for_each([this](const std::size_t p_iter) {
            push_back(p_iter);
        });
        return *this;
    };

    void push_back(const T &&t)
    {
        if (len == cap)
            grow();
        data[len] = std::move(t);
        ++len;
    };

    void push_back(const T &t)
    {
        if (len == cap)
            grow();
        data[len] = t;
        ++len;
    };

    template <typename F>
    void for_each(F f)
    {
        for (std::size_t iter = 0; iter < len; iter++)
        {
            f(data[iter]);
        }
    }

    template <typename F>
    void for_each(F f) const
    {
        for (std::size_t iter = 0; iter < len; iter++)
        {
            f(data[iter]);
        }
    }

    template <typename F>
    auto work(const std::size_t p_index, const F &f) const
        -> typename std::result_of<decltype(f)(T)>::type
    {
        // TODO :: Make this a macro that prints out current file and line
        if (p_index > len)
            std::terminate();
        return f(data[p_index]);
    }

    template <typename F>
    auto work(const std::size_t p_index, const F &f)
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

    constexpr void clear() noexcept
    {
        len = 0;
    }

private:
    T *data = nullptr;
    std::size_t len = 0u;
    std::size_t cap = 0u;

    constexpr std::size_t calculate_growth(const std::size_t p_cap)
    {
        return static_cast<std::size_t>(
                   static_cast<double>(p_cap) * growth_rate) +
               N;
    };

    void grow()
    {
        std::size_t new_size = calculate_growth(cap);
        resize(new_size);
    };

    void resize(const std::size_t p_new_cap)
    {
        T *new_data = static_cast<T *>(std::malloc(sizeof(T) * p_new_cap));
        for (std::size_t iter = 0; iter < len && iter < p_new_cap; iter++)
        {
            new_data[iter] = data[iter];
        }
        std::free(data);
        cap = p_new_cap;
        data = new_data;
    };

    void shrink()
    {
        resize(len);
    };
};
}; // namespace komunis
