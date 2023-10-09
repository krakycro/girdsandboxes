#ifndef SPACE_HPP
#define SPACE_HPP

#include <box.hpp>

namespace World
{

    class Box;

    class Space: private Container::Box
    {

        private:

        public:
            Space();
            Space(const Space& o) = delete;
            Space(const Space&&) = delete;

    };

}; // World

#endif // SPACE_HPP
