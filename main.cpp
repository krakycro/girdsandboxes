#include <iostream>
#include <memory>

#include "engine.hpp"

int main()
{
    auto GRID = std::unique_ptr<Container::Grid>(new Container::Grid(2, 2, 1));

    for(int i=0;i<GRID->get_size_x();i++)
    {
        for(int j=0;j<GRID->get_size_y();j++)
        {
                    auto b1 = GRID->at(i,j,0);
                    b1->insert();
                    auto o1 = GRID->at(i,j,0,0);
                    o1->val = 2*(i+j)+1;
                    std::cout << b1 << "|" << b1->get_self() << "-" << o1->get_key() << ":" << o1->val << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    auto b1 = GRID->at(1,1,0);
    auto b2 = GRID->at(1,0,0);
    auto o1 = (b1)->at(0);
    auto o2 = (b2)->at(0);

    std::cout << GRID->at(1,1,0) << "|" << b1 << " " << GRID->at(1,0,0) << "|" << b2 << std::endl;

    Container::Grid::swap(b1, b2);
    (b1)->insert(o2);
    //(b2)->insert(o1);

    for(int i=0;i<GRID->get_size_x();i++)
    {
        for(int j=0;j<GRID->get_size_y();j++)
        {
            auto b = GRID->at(i,j,0);
            std::cout << b << "|"  << b->get_self() << " - " ;
            for(int k=0; b->at(k) != nullptr && k < b->get_obj_size(); k++)
            {
                auto o = b->at(k);
                std::cout << o->get_key() << ":" << o->val << ", ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "asd " << __cplusplus << std::endl;
    
    return 0;
}
