cmake_minimum_required(VERSION 3.10.2)

project(komunis_std_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    komunis_std_test
    
    src/tests/test.cpp)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wpedantic -Wextra -pthread")

target_include_directories(komunis_std_test PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(komunis_std_test PRIVATE ${CMAKE_SOURCE_DIR}/thirdparty/doctest)
