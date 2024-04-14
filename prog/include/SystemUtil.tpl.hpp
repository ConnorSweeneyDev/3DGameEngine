#pragma once

#include <memory>

#include "SystemUtil.hpp"
#include "Player.hpp"
#include "Item.hpp"

template <typename Type> std::shared_ptr<Type> SystemUtil::getObjectByName(const std::string& name) const
{
    if constexpr (std::is_same<Type, Player>::value)
    {
        for (auto &player : players)
            if (player->getName() == name)
                return player;
    }
    else if constexpr (std::is_same<Type, Item>::value)
    {
        for (auto &item : items)
            if (item->getName() == name)
                return item;
    }
    return nullptr;
}