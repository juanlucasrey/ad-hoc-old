cmake_minimum_required(VERSION 2.8.8)
project (ad-hoc CXX)
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_BUILD_TYPE CMAKE_C_FLAGS_RELEASE )

include(CTest)

find_package(Boost REQUIRED)

if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	subdirs(src test)
else()
	message(FATAL_ERROR "boost is required")
endif()
