#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Camera.h"

class MouseInput {
public:
    MouseInput(bool fm, float lx, float ly);

    bool firstMouse = true;
    float lastX, lastY;

    void mouse_callback(GLFWwindow* window, double xposIn, double yposIn, Camera &camera);
    //void ProcessInput(GLFWwindow* window, Camera &camera, float deltaTime);
};