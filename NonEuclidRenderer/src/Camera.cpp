#include "Camera.h"


Camera::Camera(vec3 positionP, vec3 upP, float yawP, float pitchP, int scrWidthP, int scrHeightP) 
    : front({ 0.0f, 0.0f, -1.0f }), normalSpeed(SPEED), fastSpeed(SPEED_FAST), lookSensitivity(SENSITIVITY) 
{
    position = positionP;
    worldUp = upP;
    yaw = yawP;
    pitch = pitchP;
    screenWidth = scrWidthP;
    screenHeight = scrHeightP;
    updateCameraVectors();
}

mat4 Camera::GetViewMatrix()
{
    return lookAt(position, position + front, up);
}

// processes input received from keyboard.
void Camera::ProcessKeyboard(KeyboardInput input, float deltaTime) {
    float velocity = normalSpeed * deltaTime;
    vec3 movement = { 0,0,0 };
    int keys = 0;

    if (input.IsKeyDown(GLFW_KEY_LEFT_SHIFT))
        velocity = fastSpeed * deltaTime;

    if (input.IsKeyDown(GLFW_KEY_W)) {
        movement += front * velocity;
        keys++;
    } 
    if (input.IsKeyDown(GLFW_KEY_S)) {
        movement -= front * velocity;
        keys++;
    }
    if (input.IsKeyDown(GLFW_KEY_A)) {
        movement -= right * velocity;
        keys++;
    }
    if (input.IsKeyDown(GLFW_KEY_D)) {
        movement += right * velocity;
        keys++;
    }

    if (keys == 2) { movement /= sqrt(2); }
    
    position += movement;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= lookSensitivity;
    yoffset *= lookSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }
    updateCameraVectors();
}



void Camera::updateCameraVectors()
{
    front = normalize(vec3 {
        cos(radians(yaw))* cos(radians(pitch)),
        sin(radians(pitch)),
        sin(radians(yaw))* cos(radians(pitch))
    });
    right = normalize(cross(front, worldUp));
    up = normalize(cross(right, front));
}
