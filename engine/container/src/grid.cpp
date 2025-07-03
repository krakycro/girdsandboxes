#include <memory>
#include <vector>

#include "grid.hpp"

namespace Engine
{
    const size_t Grid::classid;

    Grid::Grid(size_t size_x, size_t size_y, size_t size_z):myclass{&Grid::classid}
    {
        this->size_x = size_x < 1 ? 1 : size_x;
        this->size_y = size_y < 1 ? 1 : size_y;
        this->size_z = size_z < 1 ? 1 : size_z;
        for(size_t i=0; i < this->size_x; i++)
        {
            this->coord.push_back(std::vector<std::vector<std::shared_ptr<Box>>>());
            for(size_t j=0; j < this->size_y; j++)
            {
                this->coord.at(i).push_back(std::vector<std::shared_ptr<Box>>());
                for(size_t k=0; k < this->size_z; k++)
                {
                    auto tmp = static_cast<std::shared_ptr<Box>>(std::make_shared<Box>());
                    tmp->set_coord(i, j, k);
                    this->coord.at(i).at(j).push_back(std::move(tmp));
                }
            }
        }
        for(size_t i=0; i < this->size_x; i++)
        {
            for(size_t j=0; j < this->size_y; j++)
            {
                for(size_t k=0; k < this->size_z; k++)
                {
                    this->coord.at(i).at(j).at(k)->set_self(&this->coord.at(i).at(j).at(k));
                }
            }
        }
    }

    void Grid::set_coord(size_t x, size_t y, size_t z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    const std::shared_ptr<Box>& Grid::at(size_t x, size_t y, size_t z)
    {
        std::shared_ptr<Box>* tmp = &Box::null;
        if((x < this->coord.size()) && (y < this->coord.at(x).size()) &&(z < this->coord.at(x).at(y).size()))
        {
            tmp = &this->coord.at(x).at(y).at(z);
        }
        else
        {
            
        }
        return *tmp;
    }

    const std::shared_ptr<Object>& Grid::at(size_t x, size_t y, size_t z, size_t o)
    {
        const std::shared_ptr<Object>* tmp = &Object::null;
        if(this->at(x, y, z) != Box::null)
        {
            tmp = &this->coord.at(x).at(y).at(z)->at(o);
        }
        else
        {
            
        }
        return *tmp;
    }

    cont_status Grid::swap(const std::shared_ptr<Box>& a, const std::shared_ptr<Box>& b)
    {
        cont_status ret = cont_status::CONT_NOK;
        if((a != Box::null) && (b != Box::null)
           && (a->get_self() != Box::null) && (b->get_self() != Box::null)
           && (a->get_self() != b->get_self())
           && (a.get() != b.get()))
        {
            auto self1 = a->point_self();
            auto self2 = b->point_self();
            auto coordA = (*self1)->get_tuple();
            auto coordB = (*self2)->get_tuple();
            auto tmp = std::move((*self1));
            (*self1) = std::move((*self2));
            (*self1)->set_coord(coordA);
            (*self2) = std::move(tmp);
            (*self2)->set_coord(coordB);
            (*self1)->set_self(self1);
            (*self2)->set_self(self2);

            ret = cont_status::CONT_OK;
        }
        else
        {
            
        }
        return ret;
    }

    size_t Grid::get_size_x() const
    {
        return this->size_x;
    }

    size_t Grid::get_size_y() const
    {
        return this->size_y;
    }

    size_t Grid::get_size_z() const
    {
        return this->size_z;
    }

}; // Engine
