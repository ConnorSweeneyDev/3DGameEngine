#pragma once

#include "rename.hpp"
#include <SDL.h>

namespace cse::platform
{
  class Window
  {
  public:
    void handle_fullscreen();

    void init();
    void cleanup();

    bool should_quit = false;
    int width;
    int height;

    sdl::Window *application;

  private:
    bool fullscreen = false;
    const int starting_pos_x = 100;
    const int starting_pos_y = 100;
    const int starting_width = 1280;
    const int starting_height = 720;

    sdl::Gl_context gl_context;
    sdl::Display_mode display_mode;
  };
  extern Window window;
}
