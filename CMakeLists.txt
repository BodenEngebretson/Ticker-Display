cmake_minimum_required(VERSION 3.20)

project(ticker_display)

add_executable(
    ticker_display
    src/main.cpp
)

set(CMAKE_CXX_STANDARD 20)
find_package(SQLite3 REQUIRED)

include_directories(ticker_display PRIVATE include database)

target_link_libraries(ticker_display PRIVATE SQLite::SQLite3)


