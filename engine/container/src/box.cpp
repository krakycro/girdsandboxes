#include <memory>

#include "box.hpp"

std::shared_ptr<Box> Box::null(nullptr);

Box::Box(){}

std::shared_ptr<Object>& Box::at(size_t key)
{
    // return this->obj.at(key);
    std::shared_ptr<Object>* tmp = &Object::null;
    if(key < this->obj.size())
    {
        auto i = this->obj.begin();
        for(auto c = 0 ; c < key ; c++)
        {
            i++;
        }
        if((i->second != nullptr)) // No need: && (this->obj.find(i->second->key) != this->obj.end()))
        {
            tmp = &this->obj.at(i->second->key);
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

void Box::insert()
{
    auto tmp = Object::Create();
    tmp->root = this->self;
    this->obj.insert({tmp->key, std::move(tmp)});
}

void Box::insert(std::shared_ptr<Object>& a)
{
    if(a != nullptr)
    {
        a->root = this->self;
        this->obj.insert({a->key, std::move(a)});
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

