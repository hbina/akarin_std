#pragma once

#include "doctest/doctest.h"
#include "vector.hpp"
#include "allocator.hpp"

#include <iostream>

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
    for (std::size_t iter = 0; iter < 16 * 16; iter++)
        vec.push_back(1u);
    CHECK(vec.capacity() == 268);
};

TEST_CASE("test komunis::vector::push_back(const T&&)")
{
    komunis::vector<
        std::size_t>
        vec;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        vec.push_back(iter);
    }
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        CHECK(vec.get_f(iter, [](const std::size_t p_iter) {
            return p_iter;
        }) == iter);
    }
};

TEST_CASE("test komunis::vector::apply_f(F f, const std::size_t)")
{
    komunis::vector<
        std::size_t>
        vec;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        vec.push_back(iter);
    }
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        vec.apply_f(iter, [](std::size_t &p_iter) -> void {
            p_iter *= 2;
        });
    }
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        CHECK(vec.get_f(iter, [](const std::size_t p_iter) {
            return p_iter;
        }) == iter * 2);
    }
};

TEST_CASE("test komunis::vector::for_each(const F& f)")
{
    komunis::vector<
        std::size_t>
        vec;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        vec.push_back(iter);
    }
    vec.for_each([](std::size_t &p_iter) {
        p_iter *= 2;
    });
    std::size_t iter = 0;
    vec.for_each([&](const std::size_t &p_iter) {
        CHECK(p_iter == iter * 2);
        iter++;
    });
};

TEST_CASE("test komunis::vector<komunis::vector>::for_each(const F& f)")
{
    komunis::vector<
        komunis::vector<std::size_t>>
        vec;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        // TODO :: Provide an easier way to initialize multidimensional vectors?
        komunis::vector<std::size_t> t_vec;
        for (std::size_t iter = 0; iter < 10; iter++)
        {
            t_vec.push_back(iter);
        }
        std::size_t counter = 0;
        t_vec.for_each([&](const std::size_t p_iter) {
            CHECK(p_iter == counter);
            ++counter;
        });
        vec.push_back(t_vec);
    }
    vec.for_each([](komunis::vector<std::size_t> &p_vec) {
        p_vec.for_each([](std::size_t &p_iter) {
            p_iter *= 5;
        });
    });
    vec.for_each([](komunis::vector<std::size_t> &p_vec) {
        std::size_t iter = 0;
        p_vec.for_each([&](std::size_t &p_iter) {
            CHECK(p_iter == iter * 5);
            iter++;
        });
    });
};

TEST_CASE("test komunis::vector::filter(const F& f)")
{
    komunis::vector<
        std::size_t>
        vec;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        vec.push_back(iter);
    }
    vec.filter([](const std::size_t p_iter) -> bool {
           return p_iter % 2;
       })
        .for_each([](const std::size_t p_iter) {
            CHECK(p_iter % 2);
        });
};

TEST_CASE("test komunis::vector::filter(const F& f)")
{
    komunis::vector<
        std::size_t>
        vec;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        vec.push_back(iter);
    }
    komunis::vector<
        std::size_t>
        vec2(std::move(vec));
    std::size_t counter = 0;
    vec2.for_each([&](const std::size_t p_iter) {
        CHECK(p_iter == counter++);
    });
    CHECK(vec.size() == 0);
};
