#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <object.hpp>

namespace Engine
{

    class Object;

    class Terrain: public Object
    {
        public:
            uint32_t density = 1;
            uint32_t quantity = 1;

        public:
            Terrain();
            Terrain(const Terrain& o) = delete;
            Terrain(const Terrain&&) = delete;
            //~Terrain() = default;

    };

}; // Engine

#endif // TERRAIN_HPP
