#include "item.hpp"

namespace Engine
{
    const size_t Item::classid;

    // Item::Item()
    // {
        
    // }

    std::shared_ptr<Item> Item::Create()
    {
        return std::static_pointer_cast<Engine::Item>(Engine::Object::BaseCreate(std::make_shared<Engine::Item>()));
    }

}; // Engine
