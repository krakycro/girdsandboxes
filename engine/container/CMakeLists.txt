
add_library(container OBJECT
            src/box.cpp 
            src/coord.cpp 
            src/grid.cpp 
            src/object.cpp)

target_include_directories(container BEFORE PUBLIC lib)
