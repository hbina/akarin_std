cmake_minimum_required(VERSION 3.10.2)

project(komunis_std_test)

add_executable(
    komunis_std_test
    
    src/tests/test.cpp)

target_include_directories(komunis_std_test PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(komunis_std_test PRIVATE ${CMAKE_SOURCE_DIR}/thirdparty/doctest)
