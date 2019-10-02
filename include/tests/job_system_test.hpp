#pragma once

#include "job_system.hpp"
#include "doctest/doctest.h"

TEST_CASE("test komunis::vector::empty()")
{
    komunis::vector<
        std::size_t>
        vec;
    CHECK(vec.empty() == true);
    vec.push_back(1u);
    CHECK(vec.empty() == false);
};
