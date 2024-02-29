#pragma once

#include <filesystem>

#include "Player.hpp"
#include "Item.hpp"

class Texture
{
    public:
        template <typename Type> void AssignTextureToObject(std::shared_ptr<Type>& object);

        template <typename Type> float CalculateObjectWidth(std::shared_ptr<Type>& object);
};
extern Texture texture;
