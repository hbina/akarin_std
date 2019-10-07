#pragma once

#include "doctest/doctest.h"
#include "map.hpp"

#include <iostream>

TEST_CASE("test ktl::map::size")
{
    ktl::map<
        std::size_t,
        std::size_t>
        map;
    map.emplace(1u, 1u);
    map.emplace(2u, 1u);
    map.emplace(3u, 1u);
    map.emplace(4u, 1u);
    map.emplace(5u, 1u);
    CHECK(map.size() == 5);
};

TEST_CASE("test ktl::map::emplace")
{
    ktl::map<
        std::size_t,
        std::size_t>
        map;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        map.emplace(iter, iter);
    }
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        CHECK(map.get_f(iter, [](const std::size_t p_iter) {
            return p_iter;
        }) == iter);
    }
};

TEST_CASE("test ktl::map::apply_f")
{
    ktl::map<
        std::size_t,
        std::size_t>
        map;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        map.emplace(iter, iter);
    }
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        map.apply_f(iter, [](std::size_t &p_iter) -> void {
            p_iter *= 2;
        });
    }
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        CHECK(map.get_f(iter, [](const std::size_t p_iter) {
            return p_iter;
        }) == iter * 2);
    }
};

TEST_CASE("test ktl::map::for_each(const F& f)")
{
    ktl::map<
        std::size_t,
        std::size_t>
        map;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        map.emplace(iter, iter);
    }
    map.for_each([](std::size_t &p_iter) {
        p_iter *= 2;
    });
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        CHECK(map[iter] == iter * 2);
    };
};

TEST_CASE("test ktl::map<ktl::map>::for_each(const F& f)")
{
    ktl::map<
        std::size_t,
        ktl::map<
            std::size_t,
            std::size_t>>
        map;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        // TODO :: Provide an easier way to initialize multidimensional vectors?
        ktl::map<std::size_t, std::size_t> t_map;
        for (std::size_t iter = 0; iter < 10; iter++)
        {
            t_map.emplace(iter, iter);
        }
        for (std::size_t iter = 0; iter < 10; iter++)
        {
            CHECK(t_map[iter] == iter);
        };
        map.emplace(iter, t_map);
    }
    map.for_each([](ktl::map<std::size_t, size_t> &p_vec) {
        p_vec.for_each([](std::size_t &p_iter) {
            p_iter *= 5;
        });
    });
    map.for_each([](const ktl::map<std::size_t, size_t> &p_vec) {
        for (std::size_t iter = 0; iter < 10; iter++)
        {
            CHECK(p_vec[iter] == iter * 5);
        };
    });
};

TEST_CASE("test ktl::map::filter")
{
    ktl::map<
        std::size_t,
        std::size_t>
        map;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        map.emplace(iter, iter);
    }
    map.filter([](const std::size_t p_iter) -> bool {
           return p_iter % 2;
       })
        .for_each([](const std::size_t p_iter) {
            CHECK(p_iter % 2);
        });
};

TEST_CASE("test ktl::map move constructor")
{
    ktl::map<
        std::size_t,
        std::size_t>
        map;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        map.emplace(iter, iter);
    }
    ktl::map<
        std::size_t,
        std::size_t>
        vec2(std::move(map));
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        CHECK(vec2[iter] == iter);
    };
    CHECK(map.size() == 0);
};

TEST_CASE("test ktl::map move assignment")
{
    ktl::map<
        std::size_t,
        std::size_t>
        map;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        map.emplace(iter, iter);
    }
    ktl::map<
        std::size_t,
        std::size_t>
        vec2 = std::move(map);
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        CHECK(vec2[iter] == iter);
    };
    CHECK(map.size() == 0);
};
