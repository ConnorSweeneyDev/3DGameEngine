#include <iostream>

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include "rename.hpp"

#include "system.hpp"

namespace cse::platform
{
    void clear_all_gl_errors() { while (gl::get_error() != GL_NO_ERROR); }

    void check_gl_error_status(const char* function_name, const char* file_name, const int line_number)
    {
        while (gl::Enum error = gl::get_error())
        {
            std::cout << "OpenGL Error " << std::hex << error << std::dec << " | Function: " << function_name << " | File: " << file_name << " | Line: " << line_number << std::endl;
            return;
        }
    }

    void sdl_init()
    {
        if (sdl::init(SDL_INIT_EVERYTHING) < 0)
        {
            std::cout << "SDL2 could not be initialized!" << std::endl;
            exit(1);
        }

        sdl::gl_set_attribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        sdl::gl_set_attribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        sdl::gl_set_attribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        sdl::gl_set_attribute(SDL_GL_DOUBLEBUFFER, 1);
        sdl::gl_set_attribute(SDL_GL_DEPTH_SIZE, 24);
        sdl::gl_set_attribute(SDL_GL_MULTISAMPLEBUFFERS, 1); // Antialiasing
        sdl::gl_set_attribute(SDL_GL_MULTISAMPLESAMPLES, 8);
        sdl::gl_set_swap_interval(0); // Vsync
    }

    void glad_init()
    {
        if (!glad::load_gl_loader(sdl::gl_get_proc_address))
        {
            std::cout << "Glad could not be initialized!" << std::endl;
            exit(1);
        }
    }
}