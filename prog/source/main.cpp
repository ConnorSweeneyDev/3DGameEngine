#include "system_util.hpp"
#include "time_util.hpp"
#include "window.hpp"
#include "render.hpp"
#include "shader.hpp"
#include "game.hpp"
#include "input.hpp"

void InitializeProgram()
{
    system_util.sdlinit();
    window.init();
    system_util.gladinit();
}

void VertexSpecification()
{
    render.SpecifyObjects();
    render.vertexcleanup();
}

void CreateGraphicsPipeline()
{
    shader.AssignShadersToObjects();
}

void InitializeGameObjects()
{
    game.objectinit();
}

void Input()
{
    input.PollWindow();
    input.PollGame();
}

void PreDraw()
{
    render.predrawinit();
    render.PreDrawObjects();
}

void Draw()
{
    render.DrawObjects();
    render.drawcleanup();
}

void MainLoop()
{
    while (!window.ShouldQuit())
    {
        time_util.UpdateDeltaTime();
        Input();

        PreDraw();
        Draw();

        SDL_GL_SwapWindow(window.getWindow());
    }
}

void CleanUpProgram()
{
    render.CleanupObjects();
    system_util.sdlcleanup();
}

int main(int argc, char* argv[])
{
    InitializeProgram();

    VertexSpecification();
    CreateGraphicsPipeline();
    InitializeGameObjects();

    MainLoop();

    CleanUpProgram();

    return 0;
}
