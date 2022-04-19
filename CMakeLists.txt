
cmake_minimum_required(VERSION 3.15)
project(motor-controller)

add_library(motor-controller include/motor-controller.h)
target_link_libraries(motor-controller i2c)
set_target_properties(motor-controller PROPERTIES LINKER_LANGUAGE CXX)
