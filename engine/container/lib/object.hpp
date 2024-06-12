#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>
#include <unordered_map>

#include "general.hpp"
#include "box.hpp"
#include "coord.hpp"

namespace Engine
{

    class Box;
    class Grid;

    //class Item;

    class Object
    {
        friend Box;
        friend Grid;

        private:
            std::shared_ptr<Box> root;
            std::shared_ptr<Object> self;

            size_t key;

            static std::unordered_map<size_t, std::shared_ptr<Object>> olist;
            static std::shared_ptr<Object> null;

        public:
            static size_t oid;
            size_t val;

            Object() = default;
            Object(const Object& o) = delete;
            Object(const Object&&) = delete;
            //virtual ~Object() = default;

            static std::shared_ptr<Object>& create();

            const Coord* get_coord() const;
            const std::shared_ptr<Box>& get_root() const;
            const std::shared_ptr<Object>& get_self();
            size_t get_key() const;

        private:
            void set_root(std::shared_ptr<Box>* root_obj);
            void set_self(std::shared_ptr<Object>& self_obj);
            void set_key(size_t new_key);

    };

}; // Engine

#endif // OBJECT_HPP
