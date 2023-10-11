#include <memory>
#include <unordered_map>

#include "object.hpp"

namespace Container
{

    size_t Object::oid = 0;
    container_ptr<Object> Object::null(nullptr);
    std::unordered_map<size_t, container_ptr<Object>> Object::olist;

    container_ptr<Object>& Object::create()
    {
        auto tmp = static_cast<container_ptr<Object>>(std::make_shared<Object>());
        tmp->self = tmp;
        tmp->key = Object::oid;
        Object::olist.insert({Object::oid, std::move(tmp)});
        // Object::olist[Object::oid]->set_self(Object::olist[Object::oid]);
        return Object::olist.at(Object::oid++);
    }

    const Coord* Object::get_coord() const
    {
        return this->root.get();
    }

    const container_ptr<Box>& Object::get_root() const
    {
        return this->root;
    }

    const container_ptr<Object>& Object::get_self()
    {
        return this->self;
    }

    size_t Object::get_key() const
    {
        return this->key;
    }

    void Object::set_root(container_ptr<Box>* root_obj)
    {
        this->root = *root_obj;
    }

    void Object::set_self(container_ptr<Object>& self_obj)
    {
        this->self = self_obj;
    }

    void Object::set_key(size_t new_key)
    {
        this->key = new_key;
    }

}; // Container
