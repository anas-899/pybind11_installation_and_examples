cmake_minimum_required(VERSION 3.0)
project(callpythonfromctest)

add_subdirectory(pybind11)

add_executable(pythoncalltest pythoncalltest.cpp)
target_link_libraries(pythoncalltest PRIVATE pybind11::embed)