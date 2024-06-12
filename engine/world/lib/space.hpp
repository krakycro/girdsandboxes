#ifndef SPACE_HPP
#define SPACE_HPP

#include <box.hpp>

namespace Engine
{

    class Box;

    class Space: public Box
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

}; // Engine

#endif // SPACE_HPP
