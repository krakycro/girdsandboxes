
add_library(world STATIC
            src/space.cpp
            src/item.cpp
            src/terrain.cpp)

target_include_directories(world BEFORE PUBLIC lib)

target_link_libraries(world container)
