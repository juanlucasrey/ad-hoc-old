cmake_minimum_required(VERSION 2.8.8)
project (ad-hoc CXX)
set(CMAKE_CXX_STANDARD 11)

include(CTest)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

subdirs(src test)
