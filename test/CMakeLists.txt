
add_subdirectory(googletest)
include_directories(googletest/include)


add_executable(testContainer container.cpp)

target_link_libraries(testContainer PRIVATE gtest)
target_link_libraries(testContainer PUBLIC engine)

target_include_directories(testContainer PUBLIC
                          "${PROJECT_SOURCE_DIR}/engine"
                          )

add_executable(test2 test2.cpp)
target_link_libraries(test2 PRIVATE gtest)



