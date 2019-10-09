#pragma once

#include "doctest/doctest.h"
#include "database.hpp"

#include <thread>
#include <vector>
#include <functional>
#include <iostream>

TEST_CASE("test ktl::database::size")
{
    ktl::database<
        std::size_t,
        std::size_t>
        map;

    std::function<void()> func = [&]() {
        for (std::size_t iter = 0; iter < 1000u; iter++)
        {
            map.emplace(iter, 1000u - iter);
        }
    };
    std::vector<std::thread> pool;
    for (std::size_t iter = 0; iter < 8; iter++)
    {
        pool.push_back(std::thread(func));
    }
    for (std::size_t iter = 0; iter < 8; iter++)
    {
        pool[iter].join();
    }
    std::size_t counter = 1000;
    map.for_each([&](const std::size_t &iter) {
        CHECK(iter == counter--);
    });
};

TEST_CASE("test ktl::database::emplace")
{
    ktl::database<
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

TEST_CASE("test ktl::database::apply_f")
{
    ktl::database<
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

TEST_CASE("test ktl::database::for_each(const F& f)")
{
    ktl::database<
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

TEST_CASE("test ktl::database<ktl::database>::for_each(const F& f)")
{
    ktl::database<
        std::size_t,
        ktl::database<
            std::size_t,
            std::size_t>>
        map;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        // TODO :: Provide an easier way to initialize multidimensional vectors?
        ktl::database<std::size_t, std::size_t> t_map;
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
    map.for_each([](ktl::database<std::size_t, size_t> &p_vec) {
        p_vec.for_each([](std::size_t &p_iter) {
            p_iter *= 5;
        });
    });
    map.for_each([](ktl::database<std::size_t, size_t> &p_vec) {
        for (std::size_t iter = 0; iter < 10; iter++)
        {
            CHECK(p_vec[iter] == iter * 5);
        };
    });
};

TEST_CASE("test ktl::database::filter")
{
    ktl::database<
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

TEST_CASE("test ktl::database move constructor")
{
    ktl::database<
        std::size_t,
        std::size_t>
        map;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        map.emplace(iter, iter);
    }
    ktl::database<
        std::size_t,
        std::size_t>
        vec2(std::move(map));
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        CHECK(vec2[iter] == iter);
    };
    CHECK(map.size() == 0);
};

TEST_CASE("test ktl::database move assignment")
{
    ktl::database<
        std::size_t,
        std::size_t>
        map;
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        map.emplace(iter, iter);
    }
    ktl::database<
        std::size_t,
        std::size_t>
        vec2 = std::move(map);
    for (std::size_t iter = 0; iter < 10; iter++)
    {
        CHECK(vec2[iter] == iter);
    };
    CHECK(map.size() == 0);
};
