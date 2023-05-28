
add_library(engine INTERFACE)

add_subdirectory(container)
add_subdirectory(world)

target_link_libraries(engine INTERFACE container world)
