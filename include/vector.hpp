#pragma once

#include <vector>

template <std::size_t p, std::size_t q, typename FP_type = double>
struct quotient
{
    static constexpr FP_type value = (FP_type)p / q;
};

std::size_t calculate_growth(const std::size_t p_cap, const double p_rate)
{
    return static_cast<std::size_t>(
        static_cast<double>(p_cap) * p_rate);
};

namespace akarin
{
template <typename T, std::size_t P = 1, std::size_t Q = 6>
struct vector
{
    static constexpr double growth_rate = P / Q;
    constexpr vector() = default;
    constexpr vector(const vector &&p_vec)
    {
        clear();
        // not enough capacity to hold content, enlarge
        if (capacity < p_vec.length)
            resize(calculate_growth(capacity, growth_rate));
        for (std::size_t ctr = 0; ctr < p_vec.length; ctr++)
            push_back(p_vec.data[ctr]);
    };

    T &operator[](const std::size_t p_idx) noexcept
    {
        return data[p_idx];
    };

    void push_back(const T &p_t) noexcept
    {
        if (length == capacity)
            resize(calculate_growth(capacity, growth_rate));
        data[length++] = p_t;
    };

    void push_back(T &&p_t) noexcept
    {
        if (length == capacity)
            resize(calculate_growth(capacity, growth_rate));
        data[length++] = std::move(p_t);
    };

    void resize(const std::size_t p_cap) noexcept
    {
        T *new_data = (T *)realloc(data, p_cap * sizeof(T));
        if (!new_data)
            std::terminate(); // no memory, your runtime is fked >3<
        for (std::size_t ctr = 0; ctr < length; ctr++)
        {
            new_data[ctr] = data[ctr];
        }
        data = new_data;
        capacity = p_cap;
    };

    void clear() noexcept
    {
        free(data);
        data = nullptr;
        length = 0;
        capacity = 0;
    };

private:
    T *data = nullptr;
    std::size_t length = 0;
    std::size_t capacity = 0;
};
}; // namespace akarin
