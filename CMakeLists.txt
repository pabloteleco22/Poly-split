project(PolySplit)

cmake_minimum_required(VERSION 3.22)

add_subdirectory(lib/poly)

add_executable(poly-split
    main.cpp
)

target_link_libraries(poly-split
    Poly
)