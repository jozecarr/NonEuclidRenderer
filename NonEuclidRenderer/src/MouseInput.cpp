#include "MouseInput.h"

//Input::Input() : firstMouse(true), lastX(0.0f), lastY(0.0f) {}

MouseInput::MouseInput(bool fm, float lx, float ly) {
    firstMouse = fm;
    lastX = lx;
    lastY = ly;
}

void MouseInput::mouse_callback(GLFWwindow* window, double xposIn, double yposIn, Camera &camera)
{
    float xpos = (float)xposIn;
    float ypos = (float)yposIn;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}