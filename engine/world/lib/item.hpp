#ifndef ITEM_HPP
#define ITEM_HPP

#include <object.hpp>

namespace Engine
{

    class Object;

    class Item: public Object
    {
        public:
            uint32_t ta = 1;
            uint32_t density = 1;

        public:
            Item() = default;
            Item(const Item& o) = delete;
            Item(const Item&&) = delete;
            //~Item() = default;


    };

}; // Engine

#endif // ITEM_HPP
