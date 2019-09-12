#pragma once

#include "pool_allocator.hpp"

namespace pool_allocator_test
{
constexpr std::size_t AKARIN_ITERATION = 300;

TEST_CASE("test akarin::vector with akarin::pool_allocator push_back")
{
    akarin::vector<std::size_t> vec;
    for (std::size_t ctr = 0; ctr < AKARIN_ITERATION; ctr++)
    {
        vec.push_back(ctr);
    }
    for (std::size_t ctr2 = 0; ctr2 < AKARIN_ITERATION; ctr2++)
    {
        CHECK(vec[ctr2] == ctr2);
    }
};

TEST_CASE("test akarin::vector with akarin::pool_allocator custom growth rate")
{
    akarin::vector<std::size_t, 20, 1> vec;
    for (std::size_t ctr = 0; ctr < AKARIN_ITERATION; ctr++)
    {
        vec.push_back(ctr);
    }
    for (std::size_t ctr = 0; ctr < AKARIN_ITERATION; ctr++)
    {
        CHECK(vec[ctr] == ctr);
    }
};

TEST_CASE("test akarin::vector with akarin::pool_allocator resize correctness")
{
    std::vector<
        std::size_t,
        akarin::pool_allocator<std::size_t>>
        vec;
    for (std::size_t ctr = 0; ctr < AKARIN_ITERATION; ctr++)
    {
        vec.push_back(ctr);
    }
    CHECK(vec.size() == AKARIN_ITERATION);

    std::vector<
        int,
        akarin::pool_allocator<int>>
        vec2;
    for (int ctr = 0; ctr < AKARIN_ITERATION; ctr++)
    {
        vec2.push_back(ctr);
    }
    CHECK(vec2.size() == AKARIN_ITERATION);
};
}; // namespace pool_allocator_test
