cmake_minimum_required(VERSION 3.16)
project(Golem LANGUAGES C)
include_directories("./include")
add_executable(Golem ./source/golem.c ./source/patcher.c)