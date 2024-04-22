#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Time {
public:

    double currentTime;
    double deltaTime;
    double frameCount;
    bool limitFrameRate;
    double targetFrameRate;
    double targetFrameTime;

    Time();
    ~Time();

    void Update();
    double GetDeltaTime() const;
    double GetAvgFrameRate() const;
    bool EveryNSeconds(double N) const;
    float GetTime() const;
    void LimitFrameRate(int targetFrameRateP);
};
