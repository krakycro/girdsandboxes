
add_executable(testContainer container.cpp)

target_link_libraries(testContainer PRIVATE gtest)
target_link_libraries(testContainer PRIVATE container)

target_include_directories(testContainer PRIVATE
    "${PROJECT_SOURCE_DIR}/test/googletest/googletest/include"
    )

target_include_directories(testContainer SYSTEM PRIVATE
    "${PROJECT_SOURCE_DIR}/engine/container"
    )
