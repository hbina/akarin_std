#pragma once

#include "doctest/doctest.h"

#include "vector.hpp"

constexpr std::size_t AKARIN_ITERATION = 10000;

TEST_CASE("test akarin::vector push_back")
{
    akarin::vector<std::size_t> vec;
    for (std::size_t ctr = 0; ctr < AKARIN_ITERATION; ctr++)
    {
        vec.push_back(ctr);
    }
    for (std::size_t ctr = 0; ctr < AKARIN_ITERATION; ctr++)
    {
        CHECK(vec[ctr] == ctr);
    }
};

TEST_CASE("test akarin::vector custom growth rate")
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