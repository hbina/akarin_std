#pragma once

#include <mutex>
#include <map>

namespace ktl
{
template <typename K, typename V>
struct database
{
    constexpr database() = default;

    constexpr database(const database &p_vec)
    {
        this->clear();
        data = p_vec.data;
    }

    constexpr database(database &&p_vec)
    {
        data = std::move(p_vec.data);
    }

    database &operator=(const database &p_vec)
    {
        if (this == &p_vec)
            return *this; // no need to copy
        this->clear();
        data = p_vec.data;
        return *this;
    }

    database &operator=(database &&p_vec)
    {
        if (this == &p_vec)
            return *this; // no need to copy
        data = std::move(p_vec.data);
        return *this;
    }

    template <typename... Args>
    void emplace(Args &&... args)
    {
        std::lock_guard<std::mutex> lock(mutex);
        data.emplace(args...);
    }

    template <typename F>
    void for_each(const F &f)
    {
        std::lock_guard<std::mutex> lock(mutex);
        for (typename std::unordered_map<K, V>::value_type &iter : data)
        {
            f(iter.second);
        }
    }

    template <typename F>
    void for_each(const F &f) const
    {
        std::lock_guard<std::mutex> lock(mutex);
        std::for_each(
            data.cbegin(),
            data.cend(),
            [&](const typename std::unordered_map<K, V>::value_type &iter) {
                f(iter.second);
            });
    }

    template <typename F>
    auto get_f(const K &p_index, const F &f) const noexcept
        -> typename std::result_of<decltype(f)(V)>::type
    {
        std::lock_guard<std::mutex> lock(mutex);
        return f(data.at(p_index));
    }

    template <typename F>
    void for_one(const K &p_index, const F &f)
    {
        std::lock_guard<std::mutex> lock(mutex);
        f(data.at(p_index));
    }

    template <typename F>
    void for_one(const K &p_index, const F &f) const
    {
        std::lock_guard<std::mutex> lock(mutex);
        f(data.at(p_index));
    }

    template <typename F>
    database<K, V> filter(const F &f) const noexcept
    {
        std::lock_guard<std::mutex> lock(mutex);
        database iterator;
        for (const typename std::unordered_map<K, V>::value_type &p_iter : data)
        {
            if (f(p_iter.second))
                iterator.emplace(p_iter.first, p_iter.second);
        }
        return iterator;
    }

    V operator[](const K &key) const noexcept
    {
        std::lock_guard<std::mutex> lock(mutex);
        return data.at(key);
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutex);
        return data.empty();
    }

    std::size_t size() const
    {
        std::lock_guard<std::mutex> lock(mutex);
        return data.size();
    }

    void clear() noexcept
    {
        std::lock_guard<std::mutex> lock(mutex);
        data.clear();
    }

private:
    mutable std::mutex mutex;
    typename std::unordered_map<K, V> data;
};
} // namespace ktl
