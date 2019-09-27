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
    constexpr vector() = default;

    constexpr vector(const vector &p_vec)
    {
        this->clear();
        p_vec.for_each([this](const T &p_iter) {
            this->push_back(p_iter);
        });
    };

    constexpr vector(const vector &&p_vec)
        : len(p_vec.len),
          cap(p_vec.cap)
    {
        std::free(data);
        data = std::move(p_vec.data);
    };

    ~vector()
    {
        std::free(data);
    };

    vector &operator=(const vector &p_vec) noexcept
    {
        if (this == &p_vec)
            return *this; // no need to copy
        this->clear();
        p_vec.for_each([this](const T &p_iter) {
            this->push_back(p_iter);
        });
        return *this;
    };

    vector &operator=(const vector &&p_vec) noexcept
    {
        if (this == &p_vec)
            return *this; // no need to copy
        std::free(data);
        data = std::move(p_vec.data);
        return *this;
    };

    template <typename... Args>
    void push_back(Args &&... args) noexcept
    {
        if (len == cap)
            grow();
        new (&data[len]) T(std::forward<Args>(args)...);
        ++len;
    };

    void push_back(const T &t) noexcept
    {
        if (len == cap)
            grow();
        data[len] = t;
        ++len;
    };

    template <typename F>
    void for_each(const F &f) noexcept
    {
        for (std::size_t iter = 0; iter < len; iter++)
        {
            f(data[iter]);
        }
    }

    template <typename F>
    void for_each(const F &f) const noexcept
    {
        for (std::size_t iter = 0; iter < len; iter++)
        {
            f(data[iter]);
        }
    }

    template <typename F>
    auto work(const std::size_t p_index, const F &f) const noexcept
        -> typename std::result_of<decltype(f)(T)>::type
    {
        // TODO :: Make this a macro that prints out current file and line
        if (p_index > len)
            std::terminate();
        return f(data[p_index]);
    }

    template <typename F>
    auto work(const std::size_t p_index, const F &f) noexcept
        -> typename std::result_of<decltype(f)(T)>::type
    {
        // TODO :: Make this a macro that prints out current file and line
        if (p_index > len)
            std::terminate();
        return f(data[p_index]);
    }

    template <typename F>
    void apply(const std::size_t p_index, F f) noexcept
    {
        // TODO :: Make this a macro that prints out current file and line
        if (p_index > len)
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

    constexpr bool empty() const noexcept
    {
        return len == 0;
    };

    constexpr std::size_t capacity() const noexcept
    {
        return cap;
    };

    constexpr std::size_t size() const noexcept
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

    static constexpr double growth_rate = static_cast<double>(Q::p) / static_cast<double>(Q::q);
    constexpr std::size_t calculate_growth(const std::size_t p_cap)
    {
        return static_cast<std::size_t>(
                   static_cast<double>(p_cap) * growth_rate) +
               N;
    };

    void grow() noexcept
    {
        std::size_t new_size = calculate_growth(cap);
        reserve(new_size);
    };

    void reserve(const std::size_t p_new_cap) noexcept
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

    void shrink() noexcept
    {
        reserve(len);
    };
};
}; // namespace komunis
