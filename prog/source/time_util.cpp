#include "SDL2/SDL_timer.h"

#include "time_util.hpp"

Time time_util;

const float& Time::getDeltaTime() const { return deltaTime; }

void Time::UpdateDeltaTime()
{
    currentTime = SDL_GetTicks64();
    deltaTime = (currentTime - lastTime);
    lastTime = currentTime;
}
