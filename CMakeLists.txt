cmake_minimum_required(VERSION 3.22)

project(PolySplit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions("-Wall -Wextra")

add_subdirectory(src/poly)

#------------------- TEST -------------------#
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

##------------------ POLY TEST ------------------##
add_executable(poly_test
    test/poly_test.cpp
)

target_link_libraries(poly_test
    GTest::gtest_main
    Poly
)
##------------------------------------------------##

include(GoogleTest)
gtest_discover_tests(poly_test)