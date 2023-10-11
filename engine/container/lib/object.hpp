#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>
#include <unordered_map>

#include "general.hpp"
#include "box.hpp"
#include "coord.hpp"

namespace Container
{

    class Box;
    class Grid;

    class Object
    {
        friend Box;
        friend Grid;

        private:
            container_ptr<Box> root;
            container_ptr<Object> self;

            size_t key;

            static size_t oid;
            static std::unordered_map<size_t, container_ptr<Object>> olist;
            static container_ptr<Object> null;

        public:
            size_t val;

            Object() = default;
            Object(const Object& o) = delete;
            Object(const Object&&) = delete;

            static container_ptr<Object>& create();

            const Coord* get_coord() const;
            const container_ptr<Box>& get_root() const;
            const container_ptr<Object>& get_self();
            size_t get_key() const;

        private:
            void set_root(container_ptr<Box>* root_obj);
            void set_self(container_ptr<Object>& self_obj);
            void set_key(size_t new_key);

    };

}; // Container

#endif // OBJECT_HPP
