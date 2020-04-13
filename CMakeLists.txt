cmake_minimum_required(VERSION 2.8)

project(recipes)

# 检查c++编译器标志，设置c++11支持变量
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORT_CXX11)
if(COMPILER_SUPPORT_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use different C++ compiler")
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-DDEBUG)
endif()

# add_subdirectory(cpp/stl/thread)

add_subdirectory(cpp/libevent)