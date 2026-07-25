cmake_minimum_required(VERSION 3.20)

project(ticker_display)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(
    ticker_display
    src/main.cpp
)

