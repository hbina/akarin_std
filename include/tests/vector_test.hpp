#pragma once

#include "doctest/doctest.h"

#include "vector.hpp"

akarin::vector<std::size_t> vec;

TEST_CASE("test akarin::vector push_back")
{
    for (std::size_t ctr = 0; ctr < 10000; ctr++)
    {
        vec.push_back(ctr);
    }
    CHECK(vec[0] == 4);
};

TEST_CASE("test akarin::vector custom growth rate")
{
    akarin::vector<std::size_t, 2, 1> vec2;
    for (std::size_t ctr = 0; ctr < 10000; ctr++)
    {
        vec2.push_back(ctr);
    }
    CHECK(vec2[0] == 4);
};