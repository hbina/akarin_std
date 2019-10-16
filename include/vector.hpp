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
        if (p_index >= data.size())
            std::terminate();
        return f(data[p_index]);
    }

    template <typename F>
    auto get_f(const std::size_t p_index, const F &f)
        -> typename std::result_of<decltype(f)(T)>::type
    {
        if (p_index >= data.size())
            std::terminate();
        return f(data[p_index]);
    }

    template <typename F>
    void for_one(const std::size_t p_index, F f)
    {
        if (p_index > data.size())
            std::terminate();
        f(data[p_index]);
    }

    template <typename F>
    vector<T> filter(const F &f) const noexcept
    {
        vector iterator;
        iterator.reserve(this->size());
        for_each([&](const T &p_iter) {
            if (f(p_iter))
                iterator.push_back(p_iter);
        });
        return iterator;
    };

    template <typename F>
    auto map(const F &f) const noexcept
        -> vector<typename std::result_of<decltype(f)(T)>::type>
    {
        vector<typename std::result_of<decltype(f)(T)>::type> iterator;
        iterator.reserve(this->size());
        for_each([&](const T &iter) {
            iterator.push_back(f(iter));
        });
        return iterator;
    };

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
    };

    constexpr void clear() noexcept
    {
        data.clear();
    };

    void reserve(const std::size_t p_new_cap)
    {
        data.reserve(p_new_cap);
    };

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

    void shrink()
    {
        data.shrink_to_fit();
    };
};
}; // namespace ktl
