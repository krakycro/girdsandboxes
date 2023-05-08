#include <memory>
#include <vector>

#include "grid.hpp"

namespace Container
{

Grid::Grid(size_t size_x, size_t size_y, size_t size_z)
{
    this->size_x = size_x < 1 ? 1 : size_x;
    this->size_y = size_y < 1 ? 1 : size_y;
    this->size_z = size_z < 1 ? 1 : size_z;
    for(int i=0; i < this->size_x; i++)
    {
        this->coord.push_back(std::vector<std::vector<container_ptr<Box>>>());
        for(int j=0; j < this->size_y; j++)
        {
            this->coord.at(i).push_back(std::vector<container_ptr<Box>>());
            for(int k=0; k < this->size_z; k++)
            {
                auto tmp = static_cast<container_ptr<Box>>(std::make_shared<Box>());
                tmp->set_self(tmp);
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

container_ptr<Box>* Grid::at(size_t x, size_t y, size_t z)
{
    container_ptr<Box>* tmp = nullptr;
    if((x < this->coord.size()) && (y < this->coord.at(x).size()) &&(z < this->coord.at(x).at(y).size()))
    {
        tmp = &this->coord.at(x).at(y).at(z);
    }
    else
    {
        
    }
    return tmp;
}

container_ptr<Object>* Grid::at(size_t x, size_t y, size_t z, size_t o)
{
    container_ptr<Object>* tmp = nullptr;
    if(this->at(x, y, z) != nullptr)
    {
        tmp = this->coord.at(x).at(y).at(z)->at(o);
    }
    else
    {
        
    }
    return tmp;
}

cont_status Grid::swap(container_ptr<Box>* a, container_ptr<Box>* b)
{
    cont_status ret = cont_status::CONT_NOK;
    if((a != nullptr) && (b != nullptr) && (a->get() != b->get()))
    {
        auto coordA = (*a)->get_coord();
        auto coordB = (*b)->get_coord();
        auto tmp = std::move(*a);
        *a = std::move(*b);
        (*a)->set_coord(coordA);
        *b = std::move(tmp);
        (*b)->set_coord(coordB);

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

}; // Container
