#pragma once

#include "doctest/doctest.h"
#include "vector.hpp"
#include "allocator.hpp"

#include <vector>

constexpr std::size_t komunis_ITERATION = 300;

TEST_CASE("test komunis::vector push_back")
{
    komunis::vector<std::size_t> vec;
    for (std::size_t ctr = 0; ctr < komunis_ITERATION; ctr++)
    {
        vec.push_back(ctr);
    }
    for (std::size_t ctr2 = 0; ctr2 < komunis_ITERATION; ctr2++)
    {
        CHECK(vec[ctr2] == ctr2);
    }
};

TEST_CASE("test komunis::vector custom growth rate")
{
    komunis::vector<std::size_t, 20, 1> vec;
    for (std::size_t ctr = 0; ctr < komunis_ITERATION; ctr++)
    {
        vec.push_back(ctr);
    }
    for (std::size_t ctr = 0; ctr < komunis_ITERATION; ctr++)
    {
        CHECK(vec[ctr] == ctr);
    }
};

TEST_CASE("test komunis::vector resize correctness")
{
    komunis::vector<std::size_t> vec;
    for (std::size_t ctr = 0; ctr < komunis_ITERATION; ctr++)
    {
        vec.push_back(ctr);
    }
    CHECK(vec.size() == komunis_ITERATION);
};

TEST_CASE("test komunis::vector resize correctness")
{
    std::vector<
        std::size_t,
        komunis::allocator<std::size_t>>
        vec;
    for (std::size_t ctr = 0; ctr < komunis_ITERATION; ctr++)
    {
        vec.push_back(ctr);
    }
    CHECK(vec.size() == komunis_ITERATION);
};