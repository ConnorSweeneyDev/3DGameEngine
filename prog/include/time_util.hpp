#pragma once

class Time
{
    public:
        const float& getDeltaTime() const;
        
        void UpdateDeltaTime();

    private:
        float deltaTime = 0.0f;
        float currentTime = 0.0f;
        float lastTime = 0.0f;
};
extern Time time_util;
