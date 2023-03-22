cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++20")

project(GridAndBoxes)

add_subdirectory(engine/container)

add_executable(GridAndBoxes main.cpp)

target_link_libraries(GridAndBoxes PUBLIC container)
target_include_directories(GridAndBoxes PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/engine/container"
                          )

add_subdirectory(test)