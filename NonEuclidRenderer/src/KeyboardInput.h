#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class keyval { public: keyval(int k, int v); int key; bool val; };

class KeyboardInput {
public:
    KeyboardInput();
    void KeyDownEvent(int key);
    void KeyUpEvent(int key);
    bool IsKeyDown(int key);
    std::vector<keyval> keysDown = {};
    void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
