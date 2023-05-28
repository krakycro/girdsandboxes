
add_library(world STATIC
            src/item.cpp)

target_include_directories(world BEFORE PUBLIC lib)
