#include "monoid.hpp"

template <typename T>
T add(const T &a, const T &b) { return a + b; }

template <typename T>
T multiply(const T &a, const T &b) { return a * b; }

TEST_CASE("test addition")
{
    ktl::monoid<int, add, 0> m1;
    ktl::monoid<int, add, 0> m2(1);
    auto m3 = m1 + m2;
    CHECK(m2 == m3);
}

TEST_CASE("test multiplication")
{
    ktl::monoid<int, multiply, 1> m1;
    ktl::monoid<int, multiply, 1> m2(2);
    auto m3 = m1 + m2;
    CHECK(m2 == m3);
}