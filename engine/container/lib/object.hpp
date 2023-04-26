#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>
#include <unordered_map>

#include "general.hpp"
#include "box.hpp"
#include "coord.hpp"

namespace Container
{

class Box;

class Object
{
public:
    std::shared_ptr<Box> root;
    std::shared_ptr<Object> self;

    size_t key;

    static size_t oid;
    static std::unordered_map<size_t, std::shared_ptr<Object>> olist;
    static std::shared_ptr<Object> null;

public:
    int val;

    Object() = default;
    Object(const Object& o) = delete;
    Object(const Object&&) = delete;

    const Coord* get_coord();

    static std::shared_ptr<Object>& create();
};

}; // Container

#endif // OBJECT_HPP
