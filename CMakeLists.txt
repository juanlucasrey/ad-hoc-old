cmake_minimum_required (VERSION 2.6)
project (ad-hoc)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

subdirs(src test)
