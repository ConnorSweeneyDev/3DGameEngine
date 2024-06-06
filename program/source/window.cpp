#include <iostream>

#include "rename.hpp"
#include <SDL.h>
#include <glad.h>

#include "window.hpp"

namespace cse::platform
{
  Window window;

  void Window::handle_move()
  {
    SDL_GetWindowPosition(window.application, &window.position_x, &window.position_y);
    display_index = (size_t)SDL_GetWindowDisplayIndex(window.application);
  }

  void Window::handle_fullscreen()
  {
    if (sdl::get_desktop_display_mode((int)display_index, &display_mode))
    {
      std::cout << "Couldn't get desktop display mode!" << std::endl;
      return;
    }

    if (fullscreen)
      fullscreen_disable();
    else
      fullscreen_enable();
  }

  void Window::init()
  {
    width = starting_width;
    height = starting_height;
    position_x = starting_position_x;
    position_y = starting_position_y;

    for (int i = 0; i < sdl::get_num_video_displays(); i++)
    {
      sdl::Rect display_bound;
      sdl::get_display_bounds(i, &display_bound);
      display_bounds.push_back(display_bound);
    }
    if (display_bounds.empty())
    {
      std::cout << "Couldn't get display bounds!" << std::endl;
      exit(1);
    }

    application =
      sdl::create_window("3D Game Engine", display_bounds[display_index].x + starting_position_x,
                         display_bounds[display_index].y + starting_position_y, starting_width,
                         starting_height, SDL_WINDOW_OPENGL);
    if (application == nullptr)
    {
      std::cout << "SDL window could not be created!" << std::endl;
      exit(1);
    }

    gl_context = sdl::gl_create_context(application);
    if (gl_context == nullptr)
    {
      std::cout << "OpenGl context could not be created!" << std::endl;
      exit(1);
    }

    if (sdl::get_desktop_display_mode(0, &display_mode))
    {
      std::cout << "Couldn't get desktop display mode!" << std::endl;
      exit(1);
    }
    if (fullscreen) fullscreen_enable();
  }

  void Window::cleanup()
  {
    sdl::gl_delete_context(gl_context);
    sdl::destroy_window(application);
    application = nullptr;

    sdl::quit();
  }

  void Window::fullscreen_disable()
  {
#ifdef _WIN32
    sdl::set_window_bordered(application, SDL_TRUE);
    sdl::set_window_size(application, starting_width, starting_height);
    sdl::set_window_position(application, position_x, position_y);
#endif
#ifdef __linux__
    sdl::set_window_fullscreen(application, 0);
    sdl::set_window_position(application, position_x, position_y);
    gl::viewport(0, 0, starting_width, starting_height);
#endif
    // #ifdef __APPLE__
    // Mac not yet supported.
    // #endif

    width = starting_width;
    height = starting_height;
    fullscreen = false;
  }

  void Window::fullscreen_enable()
  {
#ifdef _WIN32
    sdl::set_window_bordered(application, SDL_FALSE);
    sdl::set_window_size(application, display_mode.w, display_mode.h);
    sdl::set_window_position(application, SDL_WINDOWPOS_CENTERED_DISPLAY((int)display_index),
                             SDL_WINDOWPOS_CENTERED_DISPLAY((int)display_index));
#endif
#ifdef __linux__
    sdl::set_window_fullscreen(application, SDL_WINDOW_FULLSCREEN_DESKTOP);
    sdl::set_window_position(application, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    gl::viewport(0, 0, display_mode.w, display_mode.h);
#endif
    // #ifdef __APPLE__
    // Mac not yet supported.
    // #endif

    width = display_mode.w;
    height = display_mode.h;
    fullscreen = true;
  }
}
