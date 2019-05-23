cmake_minimum_required(VERSION 3.14)
project(PCModel)

set(CMAKE_CXX_STANDARD 14)

add_executable(PCModel main.cpp Process.h Process.cpp Manager.h Manager.cpp)
