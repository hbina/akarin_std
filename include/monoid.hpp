#pragma once

namespace ktl
{
template <
    typename T,
    T (*Op)(const T &, const T &),
    T Identity>
class monoid
{
    T member_value;

public:
    using value_type = T;
    constexpr monoid() : member_value(Identity){};
    constexpr monoid(const T &&t) : member_value(std::move(t)){};
    constexpr monoid operator+(const monoid &t)
    {
        if (t == Identity)
            return *this;
        return monoid(
            Op(t.member_value, member_value));
    };

    operator T() const
    {
        return member_value;
    }
};
} // namespace ktl
