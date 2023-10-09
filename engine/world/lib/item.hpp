#ifndef ITEM_HPP
#define ITEM_HPP

#include <object.hpp>

namespace World
{

    class Object;

    class Item: private Container::Object
    {

        private:

        public:
            Item();
            Item(const Item& o) = delete;
            Item(const Item&&) = delete;

    };

}; // World

#endif // ITEM_HPP
