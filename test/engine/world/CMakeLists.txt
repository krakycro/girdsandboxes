
add_executable(testWorld world.cpp)

target_link_libraries(testWorld PRIVATE gtest)
target_link_libraries(testWorld PRIVATE container)
target_link_libraries(testWorld PRIVATE world)

target_include_directories(testWorld PRIVATE
    "${PROJECT_SOURCE_DIR}/test/googletest/googletest/include"
    )

target_include_directories(testWorld SYSTEM PRIVATE
    "${PROJECT_SOURCE_DIR}/engine/container"
    "${PROJECT_SOURCE_DIR}/engine/world"
    )