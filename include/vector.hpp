#pragma once

#include <vector>

template <std::size_t p, std::size_t q, typename FP_type = double>
struct quotient
{
    static constexpr FP_type value = (FP_type)p / q;
};

namespace akarin
{
template <typename T, std::size_t P = 16, std::size_t Q = 10>
struct vector
{
    using value_type = T;
    using size_type = std::size_t;
    static constexpr double growth_rate = static_cast<double>(P) / static_cast<double>(Q);
    constexpr vector() = default;
    ~vector()
    {
        clear();
    }

    T &operator[](const std::size_t p_idx) noexcept
    {
        return data[p_idx];
    };

    T &operator[](const std::size_t p_idx) const noexcept
    {
        return data[p_idx];
    };

    void push_back(const T &p_t) noexcept
    {
        if (len == cap)
            reserve(calculate_growth(cap, growth_rate));
        data[len++] = p_t;
    };

    void push_back(T &&p_t) noexcept
    {
        if (len == cap)
            reserve(calculate_growth(cap, growth_rate));
        data[len++] = std::move(p_t);
    };

    void reserve(const std::size_t p_cap) noexcept
    {
        T *new_data = static_cast<T *>(std::malloc(p_cap * sizeof(T)));
        if (!new_data)
            std::terminate(); // no memory, your runtime is fked >3<
        for (std::size_t ctr = 0; ctr < len; ctr++)
        {
            new_data[ctr] = data[ctr];
        }
        std::free(data);
        data = new_data;
        cap = p_cap;
    };

    void clear() noexcept
    {
        std::free(data);
        data = nullptr;
        len = 0;
        cap = 0;
    };

    std::size_t size() const noexcept
    {
        return len;
    };

    std::size_t capacity() const noexcept
    {
        return cap;
    };

    bool empty() const noexcept
    {
        return len == 0;
    };

    void shrink_to_fit() noexcept
    {
        reserve(len);
    }

private:
    T *data = nullptr;
    std::size_t len = 0;
    std::size_t cap = 0;

    std::size_t calculate_growth(const std::size_t p_cap, const double p_rate)
    {
        double old_cap = static_cast<double>(p_cap);
        std::size_t new_size = static_cast<std::size_t>(old_cap * p_rate);
        return new_size + 1;
    };
};
}; // namespace akarin
