#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Time {
private:
    double currentTime;
    double deltaTime;
    int frameCount;
    bool limitFrameRate;
    double targetFrameRate;
    double targetFrameTime;

public:
    Time();
    ~Time();


    void Update();
    double GetDeltaTime() const;
    double GetFrameRate() const;
    bool EveryNSeconds(double N) const;
    float GetTime() const;
    void LimitFrameRate(int targetFrameRateP);
};
