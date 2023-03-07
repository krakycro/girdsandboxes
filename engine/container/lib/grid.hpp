#ifndef GRID_HPP
#define GRID_HPP

#include <memory>
#include <vector>

#include "coord.hpp"
#include "object.hpp"
#include "box.hpp"

class Box;
class Object;

class Grid: public Coord
{
public:
    size_t size_x, size_y, size_z;
    std::vector<std::vector<std::vector<std::shared_ptr<Box>>>> coord;

    Grid(size_t x, size_t y, size_t z);

    void set_coord(size_t x, size_t y, size_t z);

    std::shared_ptr<Box>& at(size_t x, size_t y, size_t z);

    std::shared_ptr<Object>& at(size_t x, size_t y, size_t z, size_t o);

    static void swap(std::shared_ptr<Box>& a, std::shared_ptr<Box>& b);
};

#endif // GRID_HPP