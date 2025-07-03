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

    // class Item;

    class Object
    {
        friend Box;
        friend Grid;

        private:
            static std::unordered_map<size_t, std::shared_ptr<Object>> olist;
            //static std::shared_ptr<Object> null;

            std::shared_ptr<Box> root{nullptr};
            std::shared_ptr<Object> self{Object::null};

            size_t key{0};

        public:
            static std::shared_ptr<Object> null;
            static const size_t classid = ClassFlag(CONT_LAYER_ZERO, CONT_TYPE_OBJ, CONT_ENUM_ONE);
            const size_t * const myclass;

            static size_t oid;
            size_t val;

            Object():myclass{&Object::classid} {};
            Object(const Object& o) = delete;
            Object(const Object&&) = delete;
            // virtual ~Object() = default;

            static std::shared_ptr<Object>& Create();
            static const std::shared_ptr<Object>& get_null();

            const Coord* get_coord() const;
            const std::shared_ptr<Box>& get_root() const;
            const std::shared_ptr<Object>& get_self() const;
            size_t get_key() const;
            
            static const std::unordered_map<size_t, std::shared_ptr<Object>>& GetAllObjects();

        protected:
            static std::shared_ptr<Object>& BaseCreate(std::shared_ptr<Object>&& a);
            std::shared_ptr<Object> point_self();
            void set_root(const std::shared_ptr<Box>& root_obj);
            void set_self(std::shared_ptr<Object>& self_obj);
            void set_key(size_t new_key);

            static std::unordered_map<size_t, std::shared_ptr<Object>>& get_olist();
    };

}; // Engine

#endif // OBJECT_HPP
