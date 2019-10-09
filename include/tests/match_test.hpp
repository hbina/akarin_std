#pragma once

#include "doctest/doctest.h"
#include "match.hpp"

#include <iostream>

TEST_CASE("basic std::variant test")
{
    std::variant<int, float> var;
    var = 10;
    CHECK(std::get<0>(var) == 10);
    CHECK(var.index() == 0);
    var = 10.0f;
    CHECK(std::get<1>(var) == 10.0f);
    CHECK(var.index() == 1);
};

using var_t = std::variant<int, long, double, std::string>;

template <class... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};
template <class... Ts>
overloaded(Ts...)->overloaded<Ts...>;

TEST_CASE("basic ktl::match test")
{
    std::vector<var_t> vec = {10, 15l, 1.5, "hello"};
    for (auto &v : vec)
    {
        std::visit(overloaded{
                       [](auto arg) {
                           std::cout << arg << ' ' << std::endl;
                       },
                       [](double arg) {
                           std::cout << std::fixed << arg << ' ' << std::endl;
                       },
                       [](const std::string &arg) {
                           std::cout << std::quoted(arg) << ' ' << std::endl;
                       },
                   },
                   v);
    }
};
