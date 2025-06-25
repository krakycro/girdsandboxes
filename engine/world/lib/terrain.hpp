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
            static const size_t classid = ClassFlag(CONT_LAYER_ONE, CONT_TYPE_OBJ, CONT_ENUM_TWO);
            const size_t * const myclass;

            Terrain():myclass{&Terrain::classid} {};
            Terrain(const Terrain& o) = delete;
            Terrain(const Terrain&&) = delete;
            //~Terrain() = default;

    };

}; // Engine

#endif // TERRAIN_HPP
