#ifndef ITEM_HPP
#define ITEM_HPP

#include <object.hpp>

namespace World
{

    class Object;

    class Item: public Container::Object
    {
        private:
            uint32_t density = 1;

        public:
            Item();
            Item(const Item& o) = delete;
            Item(const Item&&) = delete;

    };

}; // World

#endif // ITEM_HPP
