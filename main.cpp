#include <iostream>
#include <memory>

#include "container.hpp"

int main()
{
    auto g = Grid(2, 2, 2);
    for(int i=0;i<g.size_x;i++)
    {
        for(int j=0;j<g.size_y;j++)
        {
            for(int k=0;k<g.size_z;k++)
            {
                g.at(i,j,k)->insert();
                g.at(i,j,k)->insert();
                g.at(i,j,k,0)->val = i+j+k;
                g.at(i,j,k,1)->val = 2*(i+j+k);
            }
        }
    }

    for(auto i : Object::olist)
    {
        std::cout << i.first << ":" << i.second->key << ":" << i.second->val << ",";
    }
    std::cout << std::endl;


    Grid::swap(g.at(1,1,1),g.at(1,1,0));

    for(int i=0;i<g.size_x;i++)
    {
        for(int j=0;j<g.size_y;j++)
        {
            for(int k=0;k<g.size_z;k++)
            {
                auto t = g.at(i,j,k);
                for(auto p : t->obj)
                {
                    std::cout << p.first << ":" << p.second->val << ";";
                }
                std::cout << " ";
            }
            std::cout << ",";
        }
        std::cout << std::endl;
    }

    auto b1 = g.at(1,1,0);
    auto o1 = b1->at(0);
    auto c1 = o1->get_coord();
    auto b2 = g.at(1,1,1);
    std::cout << b1->obj.size() << b2->obj.size() << o1->val << c1->x << c1->y << c1->z << std::endl;
    b2->insert(b1->at(0));
    o1->val = 6;
    auto o2 = b2->at(0);
    auto c2 = o2->get_coord();
    std::cout << b1->obj.size() << b2->obj.size() << o2->val << c2->x << c2->y << c2->z << std::endl;
    
    for(int i=0;i<g.size_x;i++)
    {
        for(int j=0;j<g.size_y;j++)
        {
            for(int k=0;k<g.size_z;k++)
            {
                auto t = g.at(i,j,k);
                for(auto p : t->obj)
                {
                    if(p.second != nullptr) std::cout << p.first << ":" << p.second->val << ";";
                    else std::cout << p.first << ":" << "NULL;";
                }
                std::cout << " ";
            }
            std::cout << ",";
        }
        std::cout << std::endl;
    }
    
    auto o3 = b1->at(0);
    std::cout << o3.get() << std::endl;

    std::cout << "asd " << __cplusplus << std::endl;
    
    return 0;
}
