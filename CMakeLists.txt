cmake_minimum_required(VERSION 3.22)

project(PolySplit)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions("-Wall -Wextra")

add_subdirectory(lib/poly)

add_executable(poly-split
    main.cpp
)

target_link_libraries(poly-split
    Poly
)

#------------------- TEST -------------------#
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

##------------------ POINT TEST ------------------##
add_executable(point_test
    test/point_test.cpp
)

target_link_libraries(point_test
    GTest::gtest_main
    Poly
)
##------------------------------------------------##

include(GoogleTest)
gtest_discover_tests(point_test)