#ifndef BOX_HPP
#define BOX_HPP

#include <memory>
#include <unordered_map>

#include "coord.hpp"
#include "object.hpp"

class Object;

class Box: public Coord
{
public:
    // Coord coord;
    std::shared_ptr<Box> self;
    static std::shared_ptr<Box> null;
    std::unordered_map<size_t, std::shared_ptr<Object>> obj;

    Box();
    Box(const Box& o) = delete;
    Box(const Box&&) = delete;

    std::shared_ptr<Object>& at(size_t key);

    void insert();

    void insert(std::shared_ptr<Object>& a);

    static void swap(std::shared_ptr<Object>& a, std::shared_ptr<Object>& b);

};

#endif // BOX_HPP
