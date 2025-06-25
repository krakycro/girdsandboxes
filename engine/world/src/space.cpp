#include <stdio.h>

#include "space.hpp"
#include "item.hpp"


namespace Engine
{
    // template void Space::insert<Object>();
    // template void Space::insert<Item>();
    // template void Space::insert<Terrain>();

    const size_t Space::classid;

    Space::Space():myclass{&Space::classid}
    {
        
    }

    // void Space::insert()
    // {
    //     this->Engine::Box::insert();
    //     std::cout << "Space!" << std::endl;
    // }

}; // Engine
