# poly-split-mod

## Synopsis

Algorithm that solves the problem of cutting a given polygon into any number of areas of given squares with a lines of minimal length.
Based on [Algorithm by Sumit Khetarpal](http://www.khetarpal.org/polygon-splitting/).
It works for both convex and concave polygons without self-intersected edges.
This code is a modification of the one developed by [Grabarchuk Viktor](https://github.com/dhmhd/poly-split).

## Requirements

Qt >= 5.3.2.

C++ >= 17

## Compile
To use only the algorithm module you should use CMake.

`cmake -Bbuild .`

`cmake --build build -j4`

You can run the unit tests by executing `build/poly_test`

To compile the graphical application you must run `qmake` inside of the [graphics](graphics) directory.
Then type `make` and the resulting application will be called poly-split.

## Licence

Licensed under the MIT license.