#include <iostream>
#include <memory>

#include "container.hpp"

int main()
{
    auto GRID = std::unique_ptr<Container::Grid>(new Container::Grid(2, 2, 1));

    for(int i=0;i<GRID->size_x;i++)
    {
        for(int j=0;j<GRID->size_y;j++)
        {
                    GRID->at(i,j,0)->insert();
                    GRID->at(i,j,0,0)->val = 2*(i+j)+1;
                    std::cout << GRID->at(i,j,0,0) << "-" << GRID->at(i,j,0,0)->key << ":" << GRID->at(i,j,0,0)->val << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::shared_ptr<Container::Box>* b1 = &GRID->at(1,1,0);
    std::shared_ptr<Container::Box>* b2 = &GRID->at(1,0,0);

    std::cout << b1 << " " << b2 << std::endl;

    //Container::Grid::swap(GRID->at(1,1,0), GRID->at(1,0,0));
    Container::Grid::swap(*b1, *b2);

    for(int i=0;i<GRID->size_x;i++)
    {
        for(int j=0;j<GRID->size_y;j++)
        {
            std::cout << GRID->at(i,j,0,0) << "-" << GRID->at(i,j,0,0)->key << ":" << GRID->at(i,j,0,0)->val << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "asd " << __cplusplus << std::endl;
    
    return 0;
}
