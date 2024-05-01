#pragma once

#include <vector>
#include <memory>

#include <glad/glad.h>

namespace cse::object
{
    class Item
    {
        friend class Render; friend class Shader; friend class Texture;

        public:
            Item(std::string name);
            
            void init(std::vector<float> default_geometry);

            std::string name;

        private:
            GLuint vertex_array_object;
            GLuint vertex_buffer_object;
            GLuint index_buffer_object;
            GLuint shader_program;
            GLuint texture_object;
            std::string texture_path;
            int texture_width;
            int texture_height;
            int texture_channels;

            float translation_x;
            float translation_y;
            float translation_z;
            float rotation_x;
            float rotation_y;
            float rotation_z;
            float scale_x;
            float scale_y;
            float scale_z;
    };
    using Item_ptr = std::shared_ptr<Item>;
    using Item_ptr_list = std::vector<Item_ptr>;
    extern Item_ptr_list items;
}