#pragma once

#include "doctest/doctest.h"
#include "vector.hpp"
#include "allocator.hpp"

#include <vector>

TEST_CASE("test komunis::vector::empty()")
{
    komunis::vector<
        std::size_t>
        vec;
    CHECK(vec.empty() == true);
    vec.push_back(1u);
    CHECK(vec.empty() == false);
};

TEST_CASE("test komunis::vector::size()")
{
    komunis::vector<
        std::size_t>
        vec;
    vec.push_back(1u);
    vec.push_back(1u);
    vec.push_back(1u);
    vec.push_back(1u);
    vec.push_back(1u);
    CHECK(vec.size() == 5);
};

TEST_CASE("test komunis::vector::capacity()")
{
    komunis::vector<
        std::size_t>
        vec;
    vec.push_back(1u);
    vec.push_back(1u);
    vec.push_back(1u);
    vec.push_back(1u);
    vec.push_back(1u);
    vec.push_back(1u);
    vec.push_back(1u);
    vec.push_back(1u);
    vec.push_back(1u);
    CHECK(vec.capacity() == 32);
};

TEST_CASE("test komunis::vector::push_back(const T&&)")
{
    komunis::vector<
        std::size_t>
        vec;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        vec.push_back(iter * 2);
    }
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        CHECK(vec[iter] == iter * 2);
    }
};

TEST_CASE("test komunis::vector::work(F f, const std::size_t)")
{
    komunis::vector<
        std::size_t>
        vec;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        vec.push_back(iter * 2);
    }
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        CHECK(vec.work(iter, [](const std::size_t p_iter) {
            return p_iter;
        }) == iter * 2);
    }
};
