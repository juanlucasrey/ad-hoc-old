## ad-hoc

> Automatic Differentiation with High Order Calculations

CMake and Boost required: 

-for unix systems, install Boost and CMake with Brew, apt-get or another package manager

-for Windows, install CMake from https://cmake.org/download/ 

-for Windows, install Boost from (https://sourceforge.net/projects/boost/files/boost-binaries/). Make sure you install it on C:/boost otherwise CMake will not find it!

To build ad-hoc from a GitHub snapshot, do the following:

    mkdir build
    cd build
    cmake ..
    cmake --build .

To run tests, do the following:

    ctest

Or on Windows:

    ctest -C Debug   
