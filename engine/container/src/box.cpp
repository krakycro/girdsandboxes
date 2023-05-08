#include <memory>

#include "box.hpp"

namespace Container
{

// container_ptr<Box> Box::null(nullptr);

Box::Box(){}

container_ptr<Object>* Box::at(size_t i)
{
    // OLD: return this->obj.at(i);
    container_ptr<Object>* tmp = nullptr;
    if(i < this->obj.size())
    {
        auto iter = this->obj.begin();
        for(auto c = 0 ; c < i ; c++)
        {
            iter++;
        }
        if((iter->second != nullptr)) // No need: && (this->obj.find(iter->second->key) != this->obj.end()))
        {
            tmp = &this->obj.at(iter->second->get_key());
        }
        else
        {
            
        }
    }
    else
    {
        
    }
    return tmp;
}

container_ptr<Object>* Box::get(size_t key)
{
    container_ptr<Object>* tmp = nullptr;
    if(this->obj.contains(key) == true)
    {
        if(this->obj.at(key) != nullptr)
        {
            tmp = &this->obj.at(key);
        }
    }
    else
    {

    }
    return tmp;
}

void Box::insert()
{
    auto tmp = Object::create();
    tmp->set_root(this->self);
    this->obj.insert({tmp->get_key(), std::move(tmp)});
}

void Box::insert(container_ptr<Object>* a)
{
    if(a != nullptr)
    {
        (*a)->set_root(this->self);
        if(this->obj.contains((*a)->get_key()) == true)
        {
            this->obj[(*a)->get_key()] = std::move(*a);
        }
        else
        {
            this->obj.insert({(*a)->get_key(), std::move(*a)});
        }
    }
    else
    {
        
    }
}

cont_status Box::swap(container_ptr<Object>* a, container_ptr<Object>* b)
{
    cont_status ret = cont_status::CONT_NOK;
    if((a != nullptr) && (b != nullptr) && ((*a)->get_key() != (*b)->get_key()))
    { 
        auto rootA = (*a)->get_root();
        auto rootB = (*b)->get_root();
        rootA->insert(b);
        rootB->insert(a);

        ret = cont_status::CONT_OK;
    }
    else
    {
        
    }
    return ret;
}

size_t Box::get_obj_size() const 
{
    return this->obj.size();
}

void Box::set_self(const container_ptr<Box>& self_obj)
{
    this->self = self_obj;
}

}; // Container
