#ifndef ITEM_HPP
#define ITEM_HPP

#include <object.hpp>

namespace Engine
{

    class Object;

    class Item: public Object
    {
        // friend Object;

        public:
            static const size_t classid = ClassFlag(CONT_LAYER_ONE, CONT_TYPE_OBJ, CONT_ENUM_ONE);
            const size_t * const myclass;

            uint32_t ta = 1;
            uint32_t density = 1;

        public:
            Item():myclass{&Item::classid} {};
            Item(const Item& o) = delete;
            Item(const Item&&) = delete;
            //~Item() = default;

            static std::shared_ptr<Item> Create();
            // static std::shared_ptr<Object>& create();
    };

}; // Engine

#endif // ITEM_HPP
