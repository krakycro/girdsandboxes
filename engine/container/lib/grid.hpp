#ifndef GRID_HPP
#define GRID_HPP

#include <memory>
#include <vector>

#include "general.hpp"
#include "coord.hpp"
#include "object.hpp"
#include "box.hpp"

namespace Engine
{

    class Box;
    class Object;

    class Grid: public Coord
    {
        private:
            size_t size_x, size_y, size_z;
            std::vector<std::vector<std::vector<std::shared_ptr<Box>>>> coord;

        public:
            static const size_t classid = ClassFlag(CONT_LAYER_ZERO, CONT_TYPE_GRID, CONT_ENUM_ONE);
            const size_t * const myclass;

            Grid() = delete;
            Grid(const Grid& o) = delete;
            Grid(const Grid&&) = delete;
            Grid(size_t x, size_t y, size_t z);

            // std::shared_ptr<Box>* at(size_t x, size_t y, size_t z);
            const std::shared_ptr<Box>& at(size_t x, size_t y, size_t z);
            const std::shared_ptr<Object>& at(size_t x, size_t y, size_t z, size_t o);

            // static cont_status swap(std::shared_ptr<Box>* a, std::shared_ptr<Box>* b);
            static cont_status swap(std::shared_ptr<Box>& a, std::shared_ptr<Box>& b);

            size_t get_size_x() const;
            size_t get_size_y() const;
            size_t get_size_z() const;

        protected:
            void set_coord(size_t x, size_t y, size_t z);
    };

}; // Engine

#endif // GRID_HPP
