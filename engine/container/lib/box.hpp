#ifndef BOX_HPP
#define BOX_HPP

#include <memory>
#include <unordered_map>

#include "general.hpp"
#include "coord.hpp"
#include "object.hpp"

namespace Container
{

class Object;
class Grid;

class Box: public Coord
{
    friend Object;
    friend Grid;

private:
    // Coord coord;
    container_ptr<Box> self;
    std::unordered_map<size_t, container_ptr<Object>> obj;

    // static container_ptr<Box> null;

public:
    Box();
    Box(const Box& o) = delete;
    Box(const Box&&) = delete;

    container_ptr<Object>* at(size_t i);
    container_ptr<Object>* get(size_t key);

    void insert();
    void insert(container_ptr<Object>* a);

    static cont_status swap(container_ptr<Object>* a, container_ptr<Object>* b);

    // Geters/Setters
    size_t get_obj_size() const;

private:
    void set_self(const container_ptr<Box>& self_obj);
};

}; // Container

#endif // BOX_HPP
