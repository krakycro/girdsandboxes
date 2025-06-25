#include <iostream>
#include <memory>
#include <chrono>

#include "engine.hpp"

// Add global variables for grid dimensions
size_t GRID_X = 2;
size_t GRID_Y = 2;
size_t GRID_Z = 1;

int main()
{
    auto GRID = std::unique_ptr<Engine::Grid>(new Engine::Grid(GRID_X, GRID_Y, GRID_Z));
    std::cout << "Main " << __cplusplus << std::endl;

    // Start timing
    auto start = std::chrono::high_resolution_clock::now();

    for(size_t i=0;i<GRID->get_size_x();i++)
    {
        for(size_t j=0;j<GRID->get_size_y();j++)
        {
            auto b1 = GRID->at(i,j,0);
            b1->insert();
            auto o1 = GRID->at(i,j,0,0);
            o1->val = 2*(i+j)+1;
        }
    }

    // End timing and print duration
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Loop time: " << duration << " ms" << std::endl;

    return 0;
}
