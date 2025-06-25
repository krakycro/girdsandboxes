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
            static const size_t classid = ClassFlag(CONT_LAYER_ONE, CONT_TYPE_BOX, CONT_ENUM_ONE);
            const size_t * const myclass;

            Space();
            Space(const Space& o) = delete;
            Space(const Space&&) = delete;

            //using Box::insert;
            void insert();
    };

}; // Engine

#endif // SPACE_HPP
