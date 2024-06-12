#ifndef BOX_HPP
#define BOX_HPP

#include <memory>
#include <unordered_map>

#include "general.hpp"
#include "coord.hpp"
#include "object.hpp"

namespace Engine
{

    class Object;
    class Grid;

    //class Item;
    //class Terrain;

    class Box: public Coord
    {
        friend Object;
        friend Grid;

        private:
            // Coord coord;
            std::shared_ptr<Box>* self{nullptr};
            std::unordered_map<size_t, std::shared_ptr<Object>> obj;

            static std::shared_ptr<Box> null;

        public:
            Box();
            Box(const Box& o) = delete;
            Box(const Box&&) = delete;
            //virtual ~Box() = default;

            // std::shared_ptr<Object>* at(size_t i);
            const std::shared_ptr<Object>& at(size_t i);
            const std::shared_ptr<Object>& get(size_t key);

            void insert();
            void insert(std::shared_ptr<Object>& a);

            static cont_status swap(std::shared_ptr<Object>& a, std::shared_ptr<Object>& b);

            // Geters/Setters
            size_t get_obj_size() const;
            const std::shared_ptr<Box>& get_self();

        private:
            std::shared_ptr<Object>* point(size_t key);
            std::shared_ptr<Box>* point_self();
            // std::shared_ptr<std::unordered_map<size_t, std::shared_ptr<Object>>>& get_obj();

            void set_self(std::shared_ptr<Box>* self_obj);
    };

}; // Engine

#endif // BOX_HPP
