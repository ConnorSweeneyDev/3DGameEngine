#include "input.hpp"
#include "window.hpp"
#include "render.hpp"
#include "system_util.hpp"
#include "camera.hpp"
#include "player.hpp"
#include "item.hpp"

Input input;

void Input::poll_window()
{
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
            case SDL_QUIT:
                window.handle_quit();
                break;

            case SDL_KEYDOWN:
                if (keyState[SDL_SCANCODE_ESCAPE])
                    window.handle_quit();
                if (keyState[SDL_SCANCODE_F11])
                    window.handle_fullscreen();
                break;
        }
    }
}

void Input::poll_game()
{
    if (keyState[SDL_SCANCODE_H])
        camera.move_right(0.001f);
    if (keyState[SDL_SCANCODE_F])
        camera.move_left(0.001f);
    if (keyState[SDL_SCANCODE_T])
        camera.move_up(0.001f);
    if (keyState[SDL_SCANCODE_G])
        camera.move_down(0.001f);
    if (keyState[SDL_SCANCODE_Y])
        camera.move_forward(0.001f);
    if (keyState[SDL_SCANCODE_R])
        camera.move_backward(0.001f);

    if (keyState[SDL_SCANCODE_SPACE])
        camera.reset_orientation();

    // Placeholders for adding and removing objects dynamically
    if (keyState[SDL_SCANCODE_9])
    {
        render.add_object<Item>("Item 1", "prog/shader/vertex_shader.glsl", "prog/shader/fragment_shader.glsl",
                               { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.f, 1.0f, 1.0f, 1.0f });
    }
    auto item1 = system_util.get_object_by_name<Item>("Item 1");
    if (item1)
    {
        if (keyState[SDL_SCANCODE_0])
            render.remove_object(item1);
    }

    auto player1 = system_util.get_object_by_name<Player>("Player 1");
    if (player1)
    {
        if (keyState[SDL_SCANCODE_D])
            player1->move_right();
        if (keyState[SDL_SCANCODE_A])
            player1->move_left();
        if (keyState[SDL_SCANCODE_W])
            player1->move_up();
        if (keyState[SDL_SCANCODE_S])
            player1->move_down();
        if (keyState[SDL_SCANCODE_E])
            player1->move_forward();
        if (keyState[SDL_SCANCODE_Q])
            player1->move_backward();    

        if (keyState[SDL_SCANCODE_SPACE])
            player1->reset_position();
    }
    
    auto player2 = system_util.get_object_by_name<Player>("Player 2");
    if (player2)
    {
        if (keyState[SDL_SCANCODE_L])
            player2->move_right();
        if (keyState[SDL_SCANCODE_J])
            player2->move_left();
        if (keyState[SDL_SCANCODE_I])
            player2->move_up();
        if (keyState[SDL_SCANCODE_K])
            player2->move_down();
        if (keyState[SDL_SCANCODE_O])
            player2->move_forward();
        if (keyState[SDL_SCANCODE_U])
            player2->move_backward();

        if (keyState[SDL_SCANCODE_SPACE])
            player2->reset_position();
    }
}