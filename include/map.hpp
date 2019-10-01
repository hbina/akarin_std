#pragma once

#include <algorithm>
#include <unordered_map>
#include <iostream>

namespace komunis
{
template <
    typename K,
    typename V>
struct map
{
    constexpr map() = default;

    constexpr map(const map &p_vec)
    {
        this->clear();
        data = p_vec.data;
    };

    constexpr map(map &&p_vec)
    {
        data = std::move(p_vec.data);
    };

    map &operator=(const map &p_vec)
    {
        if (this == &p_vec)
            return *this; // no need to copy
        this->clear();
        data = p_vec.data;
        return *this;
    };

    map &operator=(map &&p_vec)
    {
        if (this == &p_vec)
            return *this; // no need to copy
        data = std::move(p_vec.data);
        return *this;
    };

    template <typename... Args>
    void emplace(Args &&... args)
    {
        data.emplace(args...);
    };

    template <typename F>
    void for_each(const F &f)
    {
        for (typename std::unordered_map<K, V>::value_type &iter : data)
        {
            f(iter.second);
        }
    };

    template <typename F>
    void for_each(const F &f) const
    {
        std::for_each(
            data.cbegin(),
            data.cend(),
            [&](const typename std::unordered_map<K, V>::value_type &iter) {
                f(iter.second);
            });
    };

    template <typename F>
    auto get_f(const K &p_index, const F &f) const
        -> typename std::result_of<decltype(f)(V)>::type
    {
        return f(data.at(p_index));
    };

    template <typename F>
    auto get_f(const std::size_t p_index, const F &f)
        -> typename std::result_of<decltype(f)(V)>::type
    {
        return f(data.at(p_index));
    };

    template <typename F>
    void apply_f(const std::size_t p_index, F f)
    {
        f(data.at(p_index));
    };

    template <typename F>
    map<K, V> filter(const F &f) noexcept
    {
        map iterator;
        for (const typename std::unordered_map<K, V>::value_type &p_iter : data)
        {
            if (f(p_iter.second))
                iterator.emplace(p_iter.first, p_iter.second);
        };
        return iterator;
    };

    V operator[](const K &key) const noexcept
    {
        return data.at(key);
    }

    constexpr bool empty() const
    {
        return data.empty();
    };

    constexpr std::size_t size() const
    {
        return data.size();
    }

    constexpr void clear() noexcept
    {
        data.clear();
    }

private:
    typename std::unordered_map<K, V> data;
};
}; // namespace komunis
