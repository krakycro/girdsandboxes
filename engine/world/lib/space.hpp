#ifndef SPACE_HPP
#define SPACE_HPP

#include <box.hpp>

namespace World
{

    class Box;

    class Space: public Container::Box
    {
        private:
            uint32_t volume = 0;
            uint32_t capacity = 1;

        public:
            Space();
            Space(const Space& o) = delete;
            Space(const Space&&) = delete;

            void insert();

    };

}; // World

#endif // SPACE_HPP
