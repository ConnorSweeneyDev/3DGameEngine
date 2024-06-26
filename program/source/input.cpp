#include "rename.hpp"
#include <SDL_events.h>

#include "camera.hpp"
#include "input.hpp"
#include "item.hpp"
#include "player.hpp"
#include "render.hpp"
#include "window.hpp"

namespace cse::input
{
  sdl::Event handler;
  const sdl::Uint8 *key_state = sdl::get_keyboard_state(nullptr);

  void read()
  {
    while (sdl::poll_event(&handler) != 0)
    {
      switch (handler.type)
      {
        case SDL_QUIT: system::window.should_quit = true; break;

        case SDL_WINDOWEVENT:
          if (handler.window.event == SDL_WINDOWEVENT_MOVED) system::window.handle_move();
          break;

        case SDL_KEYDOWN:
          if (key_state[SDL_SCANCODE_ESCAPE]) system::window.should_quit = true;
          if (key_state[SDL_SCANCODE_F11]) system::window.handle_fullscreen();
          break;

        default: break;
      }
    }

    if (key_state[SDL_SCANCODE_H]) object::camera.move_right(0.001f);
    if (key_state[SDL_SCANCODE_F]) object::camera.move_left(0.001f);
    if (key_state[SDL_SCANCODE_T]) object::camera.move_up(0.001f);
    if (key_state[SDL_SCANCODE_G]) object::camera.move_down(0.001f);
    if (key_state[SDL_SCANCODE_Y]) object::camera.move_forward(0.001f);
    if (key_state[SDL_SCANCODE_R]) object::camera.move_backward(0.001f);
    if (key_state[SDL_SCANCODE_SPACE]) object::camera.reset_orientation();

    // Tests for adding and removing objects dynamically
    if (key_state[SDL_SCANCODE_9])
    {
      object::render.specify_dynamic<object::Item>(
        "Item 1", "assets/redhood.png", "program/shader/vertex_shader.glsl",
        "program/shader/fragment_shader.glsl",
        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.f, 1.0f, 1.0f, 1.0f});
    }
    auto item_1 = object::render.get_by_name<object::Item>("Item 1");
    if (item_1)
    {
      if (key_state[SDL_SCANCODE_0]) object::render.remove(item_1);
    }

    if (key_state[SDL_SCANCODE_7])
    {
      object::render.specify_dynamic<object::Item>(
        "Item 2", "assets/lamp.png", "program/shader/vertex_shader.glsl",
        "program/shader/fragment_shader.glsl",
        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.f, 1.0f, 1.0f, 1.0f});
    }
    auto item_2 = object::render.get_by_name<object::Item>("Item 2");
    if (item_2)
    {
      if (key_state[SDL_SCANCODE_8]) object::render.remove(item_2);
    }

    auto player_1 = object::render.get_by_name<object::Player>("Player 1");
    if (player_1)
    {
      if (key_state[SDL_SCANCODE_D]) player_1->move_right();
      if (key_state[SDL_SCANCODE_A]) player_1->move_left();
      if (key_state[SDL_SCANCODE_W]) player_1->move_up();
      if (key_state[SDL_SCANCODE_S]) player_1->move_down();
      if (key_state[SDL_SCANCODE_E]) player_1->move_forward();
      if (key_state[SDL_SCANCODE_Q]) player_1->move_backward();
      if (key_state[SDL_SCANCODE_SPACE]) player_1->reset_position();
    }

    auto player_2 = object::render.get_by_name<object::Player>("Player 2");
    if (player_2)
    {
      if (key_state[SDL_SCANCODE_L]) player_2->move_right();
      if (key_state[SDL_SCANCODE_J]) player_2->move_left();
      if (key_state[SDL_SCANCODE_I]) player_2->move_up();
      if (key_state[SDL_SCANCODE_K]) player_2->move_down();
      if (key_state[SDL_SCANCODE_O]) player_2->move_forward();
      if (key_state[SDL_SCANCODE_U]) player_2->move_backward();
      if (key_state[SDL_SCANCODE_SPACE]) player_2->reset_position();
    }
  }
}
