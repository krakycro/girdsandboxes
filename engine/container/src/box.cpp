#include <memory>

#include "box.hpp"

namespace Container
{

    container_ptr<Box> Box::null(nullptr);

    Box::Box()
    {
        // this->obj = static_cast<container_ptr<std::unordered_map<size_t, container_ptr<Object>>>>(std::make_shared<std::unordered_map<size_t, container_ptr<Object>>>());
    }

    const container_ptr<Object>& Box::at(size_t i)
    {
        // OLD: return this->obj.at(i);
        container_ptr<Object>* tmp = &Object::null;
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
        return *tmp;
    }

    container_ptr<Object>* Box::point(size_t key)
    {
        container_ptr<Object>* tmp = &Object::null;
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

    const container_ptr<Object>& Box::get(size_t key)
    {
        return *this->point(key);
    }

    void Box::insert()
    {
        auto tmp = Object::create();
        tmp->set_root(this->point_self());
        this->obj.insert({tmp->get_key(), std::move(tmp)});
    }

    void Box::insert(container_ptr<Object>& a)
    {
        if(a != nullptr)
        {
            auto root = a->get_root();
            auto self = root->point(a->get_key());
            if(self != nullptr)
            {
                (*self)->set_root(this->point_self());
                if(this->obj.contains((*self)->get_key()) == true)
                {
                    this->obj.at((*self)->get_key()) = std::move(*self);
                }
                else
                {
                    this->obj.insert({(*self)->get_key(), std::move(*self)});
                }
            }
            else
            {

            }
        }
        else
        {
            
        }
    }

    cont_status Box::swap(container_ptr<Object>& a, container_ptr<Object>& b)
    {
        cont_status ret = cont_status::CONT_NOK;
    if((a != nullptr) && (b != nullptr) && ((a)->get_key() != (b)->get_key()))
        { 
            auto rootA = (a)->get_root();
            auto rootB = (b)->get_root();
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
        size_t tmp = 0;
        if(this != nullptr)
        {
            tmp = this->obj.size();
        }
        return tmp;
    }

    container_ptr<Box>* Box::point_self()
    {
        return this->self;
    }

    const container_ptr<Box>& Box::get_self()
    {
        return *this->self;
    }

    // container_ptr<std::unordered_map<size_t, container_ptr<Object>>>& Box::get_obj()
    // {
    //     return this->obj;
    // }

    void Box::set_self(container_ptr<Box>* self_obj)
    {
        this->self = self_obj;
    }

}; // Container
