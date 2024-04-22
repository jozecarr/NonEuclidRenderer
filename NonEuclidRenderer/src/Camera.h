#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "matrix_transform.hpp"

#include "KeyboardInput.h"

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SPEED_FAST = 7.0f;
const float SENSITIVITY = 0.1f;
const int SCR_WIDTH = 1000;
const int SCR_HEIGHT = 1000;

using glm::vec3;
using glm::lookAt;
using glm::mat4;
using glm::radians;
using glm::normalize;
using glm::cross;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors, and Matrices for use in OpenGL
class Camera {
public:
    unsigned int id;

    int screenWidth, screenHeight;

    // camera attributes
    glm::vec3 position, front, up, right, worldUp;

    // euler angles
    float yaw, pitch;

    // camera options
    float normalSpeed, fastSpeed, lookSensitivity;

    // constructor with vectors
    Camera(vec3 positionP = { 0.0f, 0.0f, 0.0f }, vec3 upP = vec3(0.0f, 1.0f, 0.0f), float yawP = YAW, float pitchP = PITCH, int scrWidthP = SCR_WIDTH, int scrHeightP = SCR_HEIGHT);

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix();

    // processes input received from any keyboard-like input system.
    void ProcessKeyboard(KeyboardInput input, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};