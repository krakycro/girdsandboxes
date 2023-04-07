#include <memory>

#include "box.hpp"

namespace Container
{

std::shared_ptr<Box> Box::null(nullptr);

Box::Box(){}

std::shared_ptr<Object>& Box::at(size_t i)
{
    // OLD: return this->obj.at(i);
    std::shared_ptr<Object>* tmp = &Object::null;
    if(i < this->obj.size())
    {
        auto iter = this->obj.begin();
        for(auto c = 0 ; c < i ; c++)
        {
            iter++;
        }
        if((iter->second != nullptr)) // No need: && (this->obj.find(iter->second->key) != this->obj.end()))
        {
            tmp = &this->obj.at(iter->second->key);
        }
        else
        {
            
        }
    }
    else
    {
        
    }
    return *tmp;
}

std::shared_ptr<Object>& Box::get(size_t key)
{
    std::shared_ptr<Object>* tmp = &Object::null;
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
    return *tmp;
}

void Box::insert()
{
    auto tmp = Object::create();
    tmp->root = this->self;
    this->obj.insert({tmp->key, std::move(tmp)});
}

void Box::insert(std::shared_ptr<Object>& a)
{
    if(a != nullptr)
    {
        a->root = this->self;
        if(this->obj.contains(a->key) == true)
        {
            this->obj[a->key] = std::move(a);
        }
        else
        {
            this->obj.insert({a->key, std::move(a)});
        }
    }
    else
    {
        
    }
}

void Box::swap(std::shared_ptr<Object>& a, std::shared_ptr<Object>& b)
{
    if((a != nullptr) && (b != nullptr) && (a->key != b->key))
    { 
        auto rootA = a->root;
        auto rootB = b->root;
        auto tmp = std::move(a);
        a = std::move(b);
        a->root = rootA;
        b = std::move(tmp);
        b->root = rootB;
    }
    else
    {
        
    }
}

}; // Container
