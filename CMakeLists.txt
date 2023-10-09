
cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++20")

project(GridAndBoxes)

add_subdirectory(engine)

add_executable(GridAndBoxes main.cpp)

target_link_libraries(GridAndBoxes PUBLIC engine)

target_include_directories(GridAndBoxes PUBLIC engine)

add_subdirectory(test)
