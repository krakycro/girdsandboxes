
add_subdirectory(googletest)
include_directories(googletest/include)

add_subdirectory(engine)

add_executable(testAll testAll.cpp)

target_link_libraries(testAll PRIVATE gtest)
target_link_libraries(testAll PRIVATE engine)

target_include_directories(testAll PRIVATE
    "${PROJECT_SOURCE_DIR}/test/googletest/googletest/include"
    )

target_include_directories(testAll SYSTEM PRIVATE
    "${PROJECT_SOURCE_DIR}/engine"
    )
