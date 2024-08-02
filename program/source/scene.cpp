#include "rename.hpp"

#include "camera.hpp"
#include "item.hpp"
#include "player.hpp"
#include "scene.hpp"

namespace cse::scene
{
  void specify_all()
  {
    object::camera.init(45.0f, 0.1f, 10.0f, glm::Vec3(0.0f, 0.0f, 3.0f),
                        glm::Vec3(0.0f, 0.0f, -1.0f), glm::Vec3(0.0f, 1.0f, 0.0f));

    for (auto &player : object::players)
    {
      if (player->name == "Player 1")
        player->init(50, 0.015f, glm::Vec3(-1.5f, -0.2f, 0.0f), glm::Vec3(0.0f, 0.0f, 0.0f),
                     glm::Vec3(1.0f, 1.0f, 1.0f));
      else if (player->name == "Player 2")
        player->init(200, 0.005f, glm::Vec3(1.5f, -0.2f, 0.0f), glm::Vec3(0.0f, 0.0f, 0.0f),
                     glm::Vec3(-1.0f, 1.0f, 1.0f));
      else
        player->init(100, 0.01f, glm::Vec3(0.0f, 0.0f, 0.0f), glm::Vec3(0.0f, 0.0f, 0.0f),
                     glm::Vec3(1.0f, 1.0f, 1.0f));
    }

    for (auto &item : object::items)
    {
      if (item->name == "Background 1")
        item->init(glm::Vec3(0.0f, 1.5f, -0.45f), glm::Vec3(0.0f, 0.0f, 0.0f),
                   glm::Vec3(10.0f, 5.0f, 1.0f));
      else if (item->name == "Background 2")
        item->init(glm::Vec3(0.0f, 1.5f, -0.3f), glm::Vec3(0.0f, 0.0f, 0.0f),
                   glm::Vec3(10.0f, 5.0f, 1.0f));
      else if (item->name == "Background 3")
        item->init(glm::Vec3(0.0f, 1.5f, -0.15f), glm::Vec3(0.0f, 0.0f, 0.0f),
                   glm::Vec3(10.0f, 5.0f, 1.0f));
      else if (item->name == "Shop")
        item->init(glm::Vec3(0.0f, 0.28f, -0.05f), glm::Vec3(0.0f, 0.0f, 0.0f),
                   glm::Vec3(3.0f, 2.0f, 1.0f));
      else if (item->name == "Floor")
        item->init(glm::Vec3(0.0f, -1.2f, 0.0f), glm::Vec3(0.0f, 0.0f, 0.0f),
                   glm::Vec3(10.0f, 1.0f, 1.0f));
      else
        item->init(glm::Vec3(0.0f, 0.0f, 0.0f), glm::Vec3(0.0f, 0.0f, 0.0f),
                   glm::Vec3(1.0f, 1.0f, 1.0f));
    }
  }
}
