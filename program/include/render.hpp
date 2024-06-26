#pragma once

#include <vector>

#include "rename.hpp"
#include <glad.h>

namespace cse::object
{
  class Render
  {
  public:
    enum class Call_action
    {
      NONE,
      CLEANUP
    };
    template <typename Type, typename Callable>
    void call_for_all(Callable callable, const Call_action action = Call_action::NONE) const;

    template <typename Type> const Object_ptr<Type> get_by_name(const std::string name) const;

    void specify();
    template <typename Type>
    void specify_dynamic(const std::string name, const std::string texture_path,
                         const std::string vertex_shader, const std::string fragment_shader,
                         const std::vector<float> default_geometry);
    template <typename Type> void remove(Object_ptr<Type> &object);

    void cleanup_all();
    void update();

  private:
    template <typename Type> const Object_ptr<Type> create(const std::string name);
    template <typename Type> void add(const std::string name);
    template <typename Type>
    const Object_ptr<Type> add_dynamic(const std::string name, const std::string texture_path,
                                       const std::string vertex_shader,
                                       const std::string fragment_shader,
                                       const std::vector<float> default_geometry);

    template <typename Type> void specify_vertices(Object_ptr<Type> &object);
    template <typename Type> void pre_draw_vertices(Object_ptr<Type> &object);
    template <typename Type> void draw_vertices(Object_ptr<Type> &object);

    void pre_draw_init();
    template <typename Type> void cleanup(Object_ptr<Type> &object);
    void vertex_cleanup();
    void draw_cleanup();

    const std::vector<gl::Float> default_quad_vertices = {
      -0.5f, -0.5f, 0.0f, // Bottom left vertex position
      1.0f,  0.0f,  0.0f, // Bottom left vertex color
      0.0f,  0.0f,        // Bottom left vertex texture coordinates
      0.5f,  -0.5f, 0.0f, // Bottom right vertex position
      0.0f,  1.0f,  0.0f, // Bottom right vertex color
      1.0f,  0.0f,        // Bottom right vertex texture coordinates
      -0.5f, 0.5f,  0.0f, // Top left vertex position
      0.0f,  0.0f,  1.0f, // Top left vertex color
      0.0f,  1.0f,        // Top left vertex texture coordinates
      0.5f,  0.5f,  0.0f, // Top right vertex position
      1.0f,  0.0f,  0.0f, // Top right vertex color
      1.0f,  1.0f         // Top right vertex texture coordinates
    };
    const std::vector<gl::Uint> default_quad_indices = {
      0, 1, 2, // Triangle 1
      2, 1, 3  // Triangle 2
    };
  };

  extern Render render;
}

#include "render.tpl.hpp"
