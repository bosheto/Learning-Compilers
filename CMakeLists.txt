cmake_minimum_required(VERSION 3.20)

project(uranium)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)


set(SOURCES 
src/main.cpp
src/parser.cpp
src/tokenization.cpp
src/generator.cpp
)

add_executable(uran ${SOURCES})