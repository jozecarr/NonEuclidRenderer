#include "KeyboardInput.h"

keyval::keyval(int k, int v) { key = k; val = v; };

KeyboardInput::KeyboardInput() {
    keysDown = {};
    for (int i = 0; i < 5000; i++)
    {
        keysDown.push_back(keyval(i, false));
    }
}

void KeyboardInput::KeyDownEvent(int key) {
    for (keyval& kv: keysDown) {
        if (kv.key == key) {
            kv.val = true; // Update the key state
            return;
        }
    }
}

void KeyboardInput::KeyUpEvent(int key) {
    // Find the key and mark it as released
    for (keyval& kv : keysDown) {
        if (kv.key == key) {
            kv.val = false; // Update the key state
            return;
        }
    }
}

bool KeyboardInput::IsKeyDown(int key) {
    // Check if the key is pressed
    for (keyval& kv : keysDown) {
        if (kv.key == key && kv.val) {
            return true;
        }
    }
    return false;
}

void KeyboardInput::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods ) {
    
    if (action == GLFW_PRESS) {
        KeyDownEvent(key);
    }
    else if (action == GLFW_RELEASE) {
        KeyUpEvent(key);
    }

    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}