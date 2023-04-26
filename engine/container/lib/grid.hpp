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
public:
    size_t size_x, size_y, size_z;
    std::vector<std::vector<std::vector<std::shared_ptr<Box>>>> coord;

public:
    Grid() = delete;
    Grid(const Grid& o) = delete;
    Grid(const Grid&&) = delete;
    Grid(size_t x, size_t y, size_t z);

    void set_coord(size_t x, size_t y, size_t z);

    std::shared_ptr<Box>& at(size_t x, size_t y, size_t z);
    std::shared_ptr<Object>& at(size_t x, size_t y, size_t z, size_t o);

    static cont_status swap(std::shared_ptr<Box>& a, std::shared_ptr<Box>& b);
};

}; // Container

#endif // GRID_HPP