#ifndef COORD_HPP
#define COORD_HPP

#include <cstddef>
#include <tuple>

#include "general.hpp"

namespace Container
{

class Coord
{
protected:
    // std::tuple<int, int, int> coord;
    size_t x;
    size_t y;
    size_t z;

public:
    Coord();
    Coord(const Coord& o) = delete;
    Coord(const Coord&&) = delete;
    Coord(size_t x, size_t y, size_t z);

    void set_coord(size_t x, size_t y, size_t z);
    void set_coord(std::tuple<size_t, size_t, size_t>& t);

    std::tuple<size_t, size_t, size_t> get_coord() const;
    size_t get_x() const;
    size_t get_y() const;
    size_t get_z() const;

};

}; // Container

#endif // COORD_HPP