#pragma once

#include "doctest/doctest.h"
#include "vector.hpp"

#include <string>

TEST_CASE("ktl::vector test empty()")
{
    ktl::vector<
        std::size_t>
        vec;
    CHECK(vec.empty() == true);
    vec.push_back(1u);
    CHECK(vec.empty() == false);
}

TEST_CASE("ktl::vector test size()")
{
    ktl::vector<
        std::size_t>
        vec;
    vec.push_back(1u);
    vec.push_back(1u);
    vec.push_back(1u);
    vec.push_back(1u);
    vec.push_back(1u);
    CHECK(vec.size() == 5);
}

TEST_CASE("ktl::vector test capacity()")
{
    ktl::vector<
        std::size_t>
        vec;
    for (std::size_t iter = 0; iter < 16 * 16; iter++)
        vec.push_back(1u);
    CHECK(vec.capacity() == 268);
}

TEST_CASE("ktl::vector get T` from some T")
{
    ktl::vector<
        std::size_t>
        vec;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        vec.push_back(iter);
    }
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        CHECK(vec.get_f(iter, [](const std::size_t p_iter) -> std::string {
            return std::to_string(p_iter);
        }) == std::to_string(iter));
    }
}

TEST_CASE("ktl::vector test ")
{
    ktl::vector<
        std::size_t>
        vec;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        vec.push_back(iter);
    }
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        vec.for_one(iter, [](std::size_t &p_iter) -> void {
            p_iter *= 2;
        });
    }
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        CHECK(vec.get_f(iter, [](const std::size_t p_iter) {
            return p_iter;
        }) == iter * 2);
    }
}

TEST_CASE("test ktl::vector::for_each(const F& f)")
{
    ktl::vector<
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
}

TEST_CASE("ktl::vector test 2 dimensional vectors")
{
    ktl::vector<
        ktl::vector<std::size_t>>
        vec;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        // TODO :: Provide an easier way to initialize multidimensional vectors?
        ktl::vector<std::size_t> t_vec;
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
    vec.for_each([](ktl::vector<std::size_t> &p_vec) {
        p_vec.for_each([](std::size_t &p_iter) {
            p_iter *= 5;
        });
    });
    vec.for_each([](ktl::vector<std::size_t> &p_vec) {
        std::size_t iter = 0;
        p_vec.for_each([&](std::size_t &p_iter) {
            CHECK(p_iter == iter * 5);
            iter++;
        });
    });
}

TEST_CASE("ktl::vector filtering functions")
{
    ktl::vector<
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
}

TEST_CASE("ktl::vector test move constructor")
{
    ktl::vector<
        std::size_t>
        vec;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        vec.push_back(iter);
    }
    ktl::vector<
        std::size_t>
        vec2(std::move(vec));
    std::size_t counter = 0;
    vec2.for_each([&](const std::size_t p_iter) {
        CHECK(p_iter == counter++);
    });
    CHECK(vec.size() == 0);
}

TEST_CASE("ktl::vector test move assignment")
{
    ktl::vector<
        std::size_t>
        vec;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        vec.push_back(iter);
    }
    ktl::vector<
        std::size_t>
        vec2 = std::move(vec);
    std::size_t counter = 0;
    vec2.for_each([&](const std::size_t p_iter) {
        CHECK(p_iter == counter++);
    });
    CHECK(vec.size() == 0);
}

TEST_CASE("ktl::vector test chaining lambdas")
{
    ktl::vector<
        std::size_t>
        vec;
    for (std::size_t iter = 0; iter < 100; iter++)
    {
        vec.push_back(iter);
    }
    vec.map([](const std::size_t iter) -> std::string {
           return std::to_string(iter);
       })
        .filter([](const std::string &iter) -> bool {
            return iter.size() < 2;
        })
        .for_each([](const std::string &iter) {
            CHECK(iter.size() == 1);
        });
}
