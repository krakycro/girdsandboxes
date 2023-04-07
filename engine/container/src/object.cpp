#include <memory>
#include <unordered_map>

#include "object.hpp"

namespace Container
{

size_t Object::oid = 0;
std::shared_ptr<Object> Object::null(nullptr);
std::unordered_map<size_t, std::shared_ptr<Object>> Object::olist;

std::shared_ptr<Object>& Object::create()
{
    auto tmp = std::make_shared<Object>();
    tmp->self = tmp;
    tmp->key = Object::oid;
    Object::olist.insert({Object::oid, std::move(tmp)});
    return Object::olist.at(Object::oid++);
}

const Coord* Object::get_coord()
{
    return this->root.get();
}

}; // Container
