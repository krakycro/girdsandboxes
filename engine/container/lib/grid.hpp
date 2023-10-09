#ifndef GRID_HPP
#define GRID_HPP

#include <memory>
#include <vector>

#include "general.hpp"
#include "coord.hpp"
#include "object.hpp"
#include "box.hpp"

namespace Container
{

    class Box;
    class Object;

    class Grid: public Coord
    {
        private:
            size_t size_x, size_y, size_z;
            std::vector<std::vector<std::vector<container_ptr<Box>>>> coord;

        public:
            Grid() = delete;
            Grid(const Grid& o) = delete;
            Grid(const Grid&&) = delete;
            Grid(size_t x, size_t y, size_t z);

            // container_ptr<Box>* at(size_t x, size_t y, size_t z);
            const container_ptr<Box>& at(size_t x, size_t y, size_t z);
            const container_ptr<Object>& at(size_t x, size_t y, size_t z, size_t o);

            // static cont_status swap(container_ptr<Box>* a, container_ptr<Box>* b);
            static cont_status swap(container_ptr<Box>& a, container_ptr<Box>& b);

            size_t get_size_x() const;
            size_t get_size_y() const;
            size_t get_size_z() const;

        private:
            void set_coord(size_t x, size_t y, size_t z);
    };

}; // Container

#endif // GRID_HPP
