#include <memory>
#include <stdio.h>

#include "box.hpp"

namespace Engine
{
    // template void Box::insert<Object>();
    // template void Box::insert<Item>();
    // template void Box::insert<Terrain>();

    std::shared_ptr<Box> Box::null(nullptr);
    const size_t Box::classid;

    Box::Box():myclass{&Box::classid}
    {
        this->set_coord(0,0,0);
        this->set_self(&Box::null);
    }

    const std::shared_ptr<Object>& Box::at(size_t i)
    {
        // OLD: return this->obj.at(i);
        std::shared_ptr<Object>* tmp = &Object::null;
        if(i < this->obj.size())
        {
            auto iter = this->obj.begin();
            for(size_t c = 0 ; c < i ; c++)
            {
                iter++;
            }
            if((iter->second != Object::null)) // No need: && (this->obj.find(iter->second->key) != this->obj.end()))
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

    std::shared_ptr<Object>* Box::point(size_t key)
    {
        std::shared_ptr<Object>* tmp = &Object::null;
        if(this->obj.size() != 0)
        {
            if(this->obj.contains(key) == true)
            {
                if(this->obj.at(key) != Object::null)
                {
                    tmp = &this->obj.at(key);
                }
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

    const std::shared_ptr<Object>& Box::get(size_t key)
    {
        return *this->point(key);
    }

    void Box::insert()
    {
        if(this->self != nullptr)
        {
            auto tmp = Object::BaseCreate(std::make_shared<Object>());
            tmp->set_root(this->get_self());
            this->obj.insert({tmp->get_key(), std::move(tmp)});
        }
    }

    void Box::insert(std::shared_ptr<Object>& a)
    {
        if(a != Object::null && a->get_self() != Object::null)
        {
            std::shared_ptr<Engine::Object> *self{nullptr};
            auto root = a->get_root();
            if(root == Box::null)
            {
                self = &a;
            }
            else
            {
                self = root->point(a->get_key());
            }
            if(self != nullptr)
            {
                (*self)->set_root(this->get_self());
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

    void Box::insert(std::shared_ptr<Object>&& a)
    {
        this->insert(a);
    }

    cont_status Box::swap(std::shared_ptr<Object>& a, std::shared_ptr<Object>& b)
    {
        cont_status ret = cont_status::CONT_NOK;
    if((a != Object::null) && (b != Object::null) && ((a)->get_key() != (b)->get_key()))
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
        return this->obj.size();
    }

    std::shared_ptr<Box>* Box::point_self()
    {
        return (this->self != nullptr)? this->self : nullptr;
    }

    const std::shared_ptr<Box>& Box::get_self() const
    {
        return (this->self != nullptr)? *this->self : Box::null;
    }

    // std::shared_ptr<std::unordered_map<size_t, std::shared_ptr<Object>>>& Box::get_obj()
    // {
    //     return this->obj;
    // }

    void Box::set_self(std::shared_ptr<Box>* self_obj)
    {
        this->self = self_obj;
    }

    const std::shared_ptr<Box>& Box::get_null()
    {
        return Box::null;
    }

}; // Engine
