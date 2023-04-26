#include <tuple>

#include "coord.hpp"

namespace Container
{

Coord::Coord(): x(0), y(0), z(0){};
Coord::Coord(size_t x, size_t y, size_t z): x(x), y(y), z(z){};

std::tuple<size_t, size_t, size_t> Coord::get_coord() const
{
    return {x, y, z};
}

void Coord::set_coord(size_t x, size_t y, size_t z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Coord::set_coord(std::tuple<size_t, size_t, size_t>& t)
{
    this->x = std::get<0>(t);
    this->y = std::get<1>(t);
    this->z = std::get<2>(t);
}

size_t Coord::get_x() const
{
    return this->x;
}

size_t Coord::get_y() const
{
    return this->y;
}

size_t Coord::get_z() const
{
    return this->z;
}

}; // Container
