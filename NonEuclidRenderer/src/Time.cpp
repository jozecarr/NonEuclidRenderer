#include "Time.h"
#include <thread>
#include <chrono>
#include <cmath>

Time::Time()
    : currentTime(glfwGetTime()), deltaTime(0.0), frameCount(0), limitFrameRate(false), targetFrameRate(60), targetFrameTime(1 / targetFrameRate) {}

Time::~Time() {}

void Time::Update() {
    double newTime = glfwGetTime();
    deltaTime = newTime - currentTime;
    currentTime = newTime;
    frameCount++;

    if (limitFrameRate) {
        double deltaDiff = targetFrameTime - deltaTime;
        if (deltaDiff > 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(static_cast<long long>(deltaDiff * 1e6)));
        }
    }
}


double Time::GetDeltaTime() const {
    return deltaTime;
}

double Time::GetAvgFrameRate() const {
    return frameCount / glfwGetTime();
}

bool Time::EveryNSeconds(double N) const {
    return fmod(currentTime, N) < deltaTime;
}

float Time::GetTime() const {
    return currentTime;
}

void Time::LimitFrameRate(int targetFrameRateP = 60) {
    limitFrameRate = true;
    targetFrameRate = targetFrameRateP;
    targetFrameTime = 1 / targetFrameRate;
}