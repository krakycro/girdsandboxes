#include <memory>
#include <unordered_map>

#include "object.hpp"

namespace Engine
{

    size_t Object::oid = 1;
    std::shared_ptr<Object> Object::null(nullptr);
    std::unordered_map<size_t, std::shared_ptr<Object>> Object::olist;

    std::shared_ptr<Object>& Object::create()
    {
        auto tmp = std::make_shared<Object>();
        tmp->self = tmp;
        tmp->key = Object::oid;
        Object::olist.insert({Object::oid, std::move(tmp)});
        // Object::olist[Object::oid]->set_self(Object::olist[Object::oid]);
        return Object::olist.at(Object::oid++);
    }

    const Coord* Object::get_coord() const
    {
        return (this->root != nullptr)? this->root.get() : nullptr;
    }

    const std::shared_ptr<Box>& Object::get_root() const
    {
        return (this->root != nullptr)? this->root : Box::null;
    }

    const std::shared_ptr<Object>& Object::get_self()
    {
        return (this->self != Object::null)? this->self : Object::null;
    }

    size_t Object::get_key() const
    {
        return this->key;
    }

    void Object::set_root(std::shared_ptr<Box>* root_obj)
    {
        this->root = *root_obj;
    }

    void Object::set_self(std::shared_ptr<Object>& self_obj)
    {
        this->self = self_obj;
    }

    void Object::set_key(size_t new_key)
    {
        this->key = new_key;
    }

    const std::shared_ptr<Object>& Object::get_null()
    {
        return Object::null;
    }

}; // Engine
