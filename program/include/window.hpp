#pragma once

#include <vector>

#include "rename.hpp"
#include <SDL.h>

namespace cse::platform
{
  class Window
  {
  public:
    void handle_move();
    void handle_fullscreen();

    void init();
    void cleanup();

    bool should_quit = false;
    int width;
    int height;

    sdl::Window *application;

  private:
    void fullscreen_disable();
    void fullscreen_enable();

    bool fullscreen = false;
    std::vector<sdl::Rect> display_bounds;
    size_t display_index = 0;
    int position_x;
    int position_y;
    const int starting_position_x = 100;
    const int starting_position_y = 100;
    const int starting_width = 1280;
    const int starting_height = 720;

    sdl::Gl_context gl_context;
    sdl::Display_mode display_mode;
  };
  extern Window window;
}
