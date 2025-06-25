#include <memory>
#include <unordered_map>

#include "object.hpp"

namespace Engine
{
    // template std::shared_ptr<Object>& Object::Create<Object>(std::shared_ptr<Object>&& a);
    // template std::shared_ptr<Item>& Object::Create<Item>(std::shared_ptr<Item>&& a);

    const size_t Object::classid;
    size_t Object::oid = 1;
    std::shared_ptr<Object> Object::null(nullptr);
    std::unordered_map<size_t, std::shared_ptr<Object>> Object::olist;

    std::shared_ptr<Object>& Object::BaseCreate(std::shared_ptr<Object>&& a)
    {
        auto tmp = a; // std::make_shared<Object>();
        auto obj = std::static_pointer_cast<Object>(tmp);
        obj->set_self(obj);
        obj->set_key(Object::oid);
        Object::get_olist().insert({Object::oid, std::move(obj)});
        // Object::olist[Object::oid]->set_self(Object::olist[Object::oid]);
        return Object::get_olist().at(Object::oid++);
    }

    std::shared_ptr<Object>& Object::Create()
    {
        return Object::BaseCreate(std::make_shared<Object>());
    }

    const Coord* Object::get_coord() const
    {
        return (this->root != nullptr)? this->root.get() : nullptr;
    }

    const std::shared_ptr<Box>& Object::get_root() const
    {
        return (this->root != nullptr)? this->root : Box::null;
    }

    const std::shared_ptr<Object>& Object::get_self() const
    {
        return (this->self != Object::null)? this->self : Object::null;
    }

    size_t Object::get_key() const
    {
        return this->key;
    }

    void Object::set_root(const std::shared_ptr<Box>& root_obj)
    {
        this->root = root_obj;
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

    std::unordered_map<size_t, std::shared_ptr<Object>>& Object::get_olist()
    {
        return Object::olist;
    }

}; // Engine
