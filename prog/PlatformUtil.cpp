#include "PlatformUtil.hpp"

PlatformUtil platformUtil;

void PlatformUtil::ClearAllGLErrors() // OpenGL errors can stack up, so this clears them all
{
    while (glGetError() != GL_NO_ERROR);
}
bool PlatformUtil::CheckGLErrorStatus(const char* functionName, const char* fileName, int line) // Checks for errors and displays them
{
    while (GLenum error = glGetError())
    {
        std::cout << "OpenGL Error " << std::hex << error << std::dec << "!" // OpenGL errors are in hex
                  << "    Function: " << functionName
                  << "    File: " << fileName
                  << "    Line: " << line << std::endl;
        return true;
    }

    return false;
}

void PlatformUtil::GetOpenGLVersionInfo()
{
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl; 
}

void PlatformUtil::sdlinit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL2 could not be initialized!" << std::endl;
        exit(1);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Double buffering enabled
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);  // 24 layers of depth
}
void PlatformUtil::gladinit()
{
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) // Loads OpenGL functions using GLAD
    {
        std::cout << "Glad could not be initialized!" << std::endl;
        exit(1);
    }
}
