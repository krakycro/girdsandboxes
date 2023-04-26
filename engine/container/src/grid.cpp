#include <memory>
#include <vector>

#include "grid.hpp"

namespace Container
{

Grid::Grid(size_t size_x, size_t size_y, size_t size_z)
{
    this->size_x = size_x;
    this->size_y = size_y;
    this->size_z = size_z;
    for(int i=0; i < size_x; i++)
    {
        this->coord.push_back(std::vector<std::vector<std::shared_ptr<Box>>>());
        for(int j=0; j < size_y; j++)
        {
            this->coord.at(i).push_back(std::vector<std::shared_ptr<Box>>());
            for(int k=0; k < size_z; k++)
            {
                auto tmp = std::make_shared<Box>();
                tmp->self = tmp;
                tmp->set_coord(i, j, k);
                this->coord.at(i).at(j).push_back(std::move(tmp));
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

std::shared_ptr<Box>& Grid::at(size_t x, size_t y, size_t z)
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

std::shared_ptr<Object>& Grid::at(size_t x, size_t y, size_t z, size_t o)
{
    std::shared_ptr<Object>* tmp = &Object::null;
    if(this->at(x, y, z) != nullptr)
    {
        tmp = &this->coord.at(x).at(y).at(z)->at(o);
    }
    else
    {
        
    }
    return *tmp;
}

cont_status Grid::swap(std::shared_ptr<Box>& a, std::shared_ptr<Box>& b)
{
    cont_status ret = cont_status::CONT_NOK;
    if((a != nullptr) && (b != nullptr) && (a.get() != b.get()))
    {
        auto coordA = a->get_coord();
        auto coordB = b->get_coord();
        auto tmp = std::move(a);
        a = std::move(b);
        a->set_coord(coordA);
        b = std::move(tmp);
        b->set_coord(coordB);

        ret = cont_status::CONT_OK;
    }
    else
    {
        
    }
    return ret;
}

}; // Container
