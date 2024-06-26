#define STB_IMAGE_IMPLEMENTATION

#include "texture.hpp"
#include "item.hpp"
#include "player.hpp"

namespace cse::object
{
  Texture texture;

  void Texture::specify()
  {
    for (auto &player : players)
    {
      if (player->name == "Player 1")
        player->texture_path = "assets/redhood.png";
      else if (player->name == "Player 2")
        player->texture_path = "assets/redhood.png";
      else
        player->texture_path = "assets/empty.png";

      load(player);
    }

    for (auto &item : items)
    {
      if (item->name == "Background 1")
        item->texture_path = "assets/background1.png";
      else if (item->name == "Background 2")
        item->texture_path = "assets/background2.png";
      else if (item->name == "Background 3")
        item->texture_path = "assets/background3.png";
      else if (item->name == "Shop")
        item->texture_path = "assets/shop.png";
      else if (item->name == "Floor")
        item->texture_path = "assets/leaffloor.png";
      else
        item->texture_path = "assets/empty.png";

      load(item);
    }
  }

  void Texture::load_cleanup()
  {
    gl::bind_vertex_array(0);
    gl::bind_buffer(GL_ARRAY_BUFFER, 0);
    gl::bind_buffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    gl::bind_texture(GL_TEXTURE_2D, 0);
  }
}
