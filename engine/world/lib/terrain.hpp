#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <object.hpp>

namespace World
{

    class Object;

    class Terrain: public Container::Object
    {
        private:
            uint32_t density = 1;
            uint32_t quantity = 1;

        public:
            Terrain();
            Terrain(const Terrain& o) = delete;
            Terrain(const Terrain&&) = delete;

    };

}; // World

#endif // TERRAIN_HPP
