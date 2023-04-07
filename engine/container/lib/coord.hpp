#ifndef COORD_HPP
#define COORD_HPP

#include <cstddef>
#include <tuple>

namespace Container
{

class Coord
{
public:
    // std::tuple<int, int, int> coord;
    size_t x;
    size_t y;
    size_t z;

    void set_coord(size_t x, size_t y, size_t z);

public:
    Coord();
    Coord(const Coord& o) = delete;
    Coord(const Coord&&) = delete;
    Coord(size_t x, size_t y, size_t z);

    std::tuple<size_t, size_t, size_t> get_coord() const;

    void set_coord(std::tuple<size_t, size_t, size_t>& t);

};

}; // Container

#endif // COORD_HPP