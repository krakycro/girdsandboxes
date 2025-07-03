#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <cstddef>
#include <tuple>
#include <memory>
#include <iostream>

namespace Engine
{
    enum cont_status
    {
        CONT_OK = 0,
        CONT_NOK,
    };

    enum cont_class_flag
    {
        CONT_FLAG_GRID = 0x000000FF,
        CONT_FLAG_BOX  = 0x0000FF00,
        CONT_FLAG_OBJ  = 0x00FF0000,
        CONT_FLAG_DAT  = 0x00FFFFFF,
        CONT_FLAG_LVL  = 0xFF000000,
    };

    enum cont_class_type
    {
        CONT_TYPE_GRID = 0,
        CONT_TYPE_BOX  = 8,
        CONT_TYPE_OBJ  = 16,
        CONT_TYPE_LVL  = 24,
    };

    enum cont_class_layer
    {
        CONT_LAYER_ZERO  = 0,
        CONT_LAYER_ONE   = 1,
        CONT_LAYER_TWO   = 2,
        CONT_LAYER_THREE = 3,
    };

    enum cont_class_enum
    {
        CONT_ENUM_ONE   = 1,
        CONT_ENUM_TWO   = 2,
        CONT_ENUM_THREE = 3,
        CONT_ENUM_FOUR  = 4,
    };

    constexpr size_t ClassFlag(const cont_class_layer layer, const cont_class_type type, const cont_class_enum var)
    {
        return (layer << CONT_TYPE_LVL) | ((var) << type);
    };

}; // Engine

#endif // GENERAL_HPP
