#pragma once

#include <algorithm>
#include <cstddef>
#include <type_traits>
#include <vector>

namespace ktl
{
template <std::size_t P, std::size_t Q>
struct quotient
{
    static constexpr std::size_t p = P;
    static constexpr std::size_t q = Q;
};

// TODO :: Provide template arguments to allocators.
template <
    typename T,
    typename Q = quotient<16, 10>,
    std::size_t N = 4>
struct vector
{
    constexpr vector() = default;

    constexpr vector(const vector &p_vec)
    {
        this->clear();
        data = p_vec.data;
    };

    constexpr vector(vector &&p_vec)
    {
        data = std::move(p_vec.data);
    };

    vector &operator=(const vector &p_vec)
    {
        if (this == &p_vec)
            return *this; // no need to copy
        this->clear();
        data = p_vec.data;
        return *this;
    };

    vector &operator=(vector &&p_vec)
    {
        if (this == &p_vec)
            return *this; // no need to copy
        data = std::move(p_vec.data);
        return *this;
    };

    template <typename... Args>
    void push_back(Args &&... args)
    {
        if (data.size() == data.capacity())
            grow();
        data.push_back(args...);
    };

    void push_back(const T &t)
    {
        if (data.size() == data.capacity())
            grow();
        data.push_back(t);
    };

    template <typename F>
    void for_each(const F &f)
    {
        for (T &elem : data)
        {
            f(elem);
        }
    }

    template <typename F>
    void for_each(const F &f) const
    {
        std::for_each(data.cbegin(), data.cend(), f);
    }

    template <typename F>
    auto get_f(const std::size_t p_index, const F &f) const
        -> typename std::result_of<decltype(f)(T)>::type
    {
        // TODO :: Make this a macro that prints out current file and line
        if (p_index >= data.size())
            std::terminate();
        return f(data[p_index]);
    }

    template <typename F>
    auto get_f(const std::size_t p_index, const F &f)
        -> typename std::result_of<decltype(f)(T)>::type
    {
        // TODO :: Make this a macro that prints out current file and line
        if (p_index >= data.size())
            std::terminate();
        return f(data[p_index]);
    }

    template <typename F>
    void apply_f(const std::size_t p_index, F f)
    {
        // TODO :: Make this a macro that prints out current file and line
        if (p_index > data.size())
            std::terminate();
        f(data[p_index]);
    }

    template <typename F>
    vector<std::size_t> filter(const F &f) noexcept
    {
        vector iterator;
        for_each([&](const T &p_iter) {
            if (f(p_iter))
                iterator.push_back(p_iter);
        });
        return iterator;
    }

    constexpr bool empty() const
    {
        return data.empty();
    };

    constexpr std::size_t capacity() const
    {
        return data.capacity();
    };

    constexpr std::size_t size() const
    {
        return data.size();
    }

    constexpr void clear() noexcept
    {
        data.clear();
    }

    // Helpers for use with std::algorithm's
    // TODO :: Should this API exists?
    auto cbegin() const noexcept
        -> decltype(std::declval<std::vector<T>>().cbegin())
    {
        return data.cbegin();
    }

    auto cend() const noexcept
        -> decltype(std::declval<std::vector<T>>().cend())
    {
        return data.cend();
    }

    auto begin() const noexcept
        -> decltype(std::declval<std::vector<T>>().begin())
    {
        return data.begin();
    }

    auto end() const noexcept
        -> decltype(std::declval<std::vector<T>>().end())
    {
        return data.end();
    }

private:
    typename std::vector<T> data;

    static constexpr double growth_rate = static_cast<double>(Q::p) / static_cast<double>(Q::q);
    constexpr std::size_t calculate_growth(const std::size_t p_cap)
    {
        return static_cast<std::size_t>(
                   static_cast<double>(p_cap) * growth_rate) +
               N;
    };

    void grow()
    {
        std::size_t new_size = calculate_growth(data.capacity());
        reserve(new_size);
    };

    void reserve(const std::size_t p_new_cap)
    {
        data.reserve(p_new_cap);
    };

    void shrink()
    {
        data.shrink_to_fit();
    };
};
}; // namespace ktl
