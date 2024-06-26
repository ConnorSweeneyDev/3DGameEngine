#pragma once

#include <iostream>

#include "rename.hpp"
#include "stb_image.h"
#include <glad.h>

#include "texture.hpp"

namespace cse::object
{
  template <typename Type> void Texture::load(Object_ptr<Type> &object)
  {
    load_init(object);
    stbi::set_flip_vertically_on_load(true);

    unsigned char *image_data = stbi::load(object->texture_path.c_str(), &object->texture_width,
                                           &object->texture_height, &object->texture_channels, 0);
    if (!image_data)
    {
      std::cout << "Failed to load " << object->texture_path << "!" << std::endl;
      return;
    }

    if (object->name == "Player 1" || object->name == "Player 2")
    {
      int offset = 0;
      int section_width = 50;
      int section_height = 50;
      int channels = object->texture_channels;
      unsigned char *source_image_data = image_data + (section_width * offset) * channels;
      unsigned char *destination_image_data =
        new unsigned char[(size_t)(section_width * section_height * channels)];

      for (int y = 0; y < section_height; ++y)
      {
        for (int x = 0; x < section_width; ++x)
        {
          int source_index = (y * object->texture_width + x) * channels;
          int destination_index = (y * section_width + x) * channels;

          destination_image_data[destination_index + 0] = source_image_data[source_index + 0];
          destination_image_data[destination_index + 1] = source_image_data[source_index + 1];
          destination_image_data[destination_index + 2] = source_image_data[source_index + 2];
          destination_image_data[destination_index + 3] = source_image_data[source_index + 3];
        }
      }

      gl::tex_image_2d(GL_TEXTURE_2D, 0, GL_RGBA, section_width, section_height, 0, GL_RGBA,
                       GL_UNSIGNED_BYTE, destination_image_data);
      delete[] destination_image_data;
    }
    else
    {
      gl::tex_image_2d(GL_TEXTURE_2D, 0, GL_RGBA, object->texture_width, object->texture_height, 0,
                       GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    }

    stbi::image_free(image_data);
    load_cleanup();
  }

  template <typename Type> void Texture::load_init(Object_ptr<Type> &object)
  {
    gl::bind_vertex_array(object->vertex_array_object);
    gl::bind_buffer(GL_ARRAY_BUFFER, object->vertex_buffer_object);
    gl::bind_buffer(GL_ELEMENT_ARRAY_BUFFER, object->index_buffer_object);
    gl::bind_texture(GL_TEXTURE_2D, object->texture_object);
  }
}
