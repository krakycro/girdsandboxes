#include <stdio.h>

#include "space.hpp"
#include "item.hpp"


namespace World
{
    template void Space::insert<Container::Object>();
    template void Space::insert<Item>();

    Space::Space()
    {
        
    }

    template<class T> void Space::insert()
    {
        //this->Container::Box::insert<T>();
        std::cout << "FAKE!" << std::endl;
    }

}; // World
