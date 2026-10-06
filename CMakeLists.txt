cmake_minimum_required(VERSION 3.20)

project(ticker_display)

add_executable(
    ticker_display
    src/main.cpp
)

set(CMAKE_CXX_STANDARD 20)

include_directories(ticker_display PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/database)

target_link_libraries(ticker_display)


