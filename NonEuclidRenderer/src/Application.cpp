#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
using std::cout; using std::endl;
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h" 

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "KeyboardInput.h"
#include "MouseInput.h"
#include "GameObject.h"
#include "World.h"
#include "Time.h"

#include "Demo.h"

//settings

const unsigned int SCREEN_WIDTH = 1920;
const unsigned int SCREEN_HEIGHT = 1080;

Camera mainCamera(vec3(0.0f, 3.5f, 15.0f));
Camera secondaryCamera(vec3(10.0f, 10.0f, -5.0f));
Camera* cameras[2] = { &mainCamera, &secondaryCamera };

MouseInput mouseInput(true, SCR_WIDTH / 2.0f, SCR_HEIGHT / 2.0);
KeyboardInput keyboardInput = KeyboardInput();

float cubeVertices[36 * 5] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

int main(void){
    GLFWwindow* window;
    mainCamera.screenWidth = SCREEN_WIDTH;
    mainCamera.screenHeight = SCREEN_HEIGHT;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glEnable(GL_CULL_FACE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "NON-EUCLIDEAN PROJ", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // set mouse input callback, use lambda function for mouse input classe func
    glfwSetCursorPosCallback(window, [](GLFWwindow* win, double xpos, double ypos) {
        mouseInput.mouse_callback(win, xpos, ypos, mainCamera);
    });

    //set keyboard input callbacks
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        keyboardInput.KeyCallback(window, key, scancode, action, mods);
    });

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glewInit() != GLEW_OK)
        std::cout << "glewInit fail" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);

    {
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(cubeVertices, 6 * 6 * 5 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
        vb.Unbind();

        Renderer renderer;

        Time time;
        //time.LimitFrameRate(60);

        printf("%s\n", glGetString(GL_VERSION));

        World world = World();
        
        ///////////////////////////////////
        Texture texture("res/textures/checks_HD.png");
        texture.Bind(1);

        Shader* newShader1 = GetBasicShader({1,1,1});
        Shader* newShader2 = GetBasicShader({1,1,0});
        Shader* newShader3 = GetBasicShader({1,0,1});
        Shader* newShader4 = GetBasicShader({1,0,0});
        Shader* newShader5 = GetBasicShader({0,1,1});
        Shader* newShader6 = GetBasicShader({0,1,0});
        Shader* newShader7 = GetBasicShader({0,0,1});
        Shader* newShader8 = GetBasicShader({0,0,0});

        Object* obj4 = new Object(newShader5, { 10,1,10 }, { 0,0,0 }, { 0,0,0 }, { 1, 0 });
        world.AddObject(obj4);

        Object* obj5 = new Object(newShader6, { 1,1.5f,3 }, { 0,5,0 }, { 0,30,0 }, { 1, 1 });
        world.AddObject(obj5);

        /////////////////////////////////

        //main loop
        while (!glfwWindowShouldClose(window))
        {
            time.Update();
            mainCamera.ProcessKeyboard(keyboardInput, time.GetDeltaTime());

            glClearColor(1, 1, 1, 1);
            GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

            world.Update(time.GetDeltaTime());
                        
            if (time.EveryNSeconds(5)) {
                cout << "Average frame rate = " << time.GetAvgFrameRate() << "(" << time.frameCount << " frames in " << glfwGetTime() << " seconds) \n";
            }

            renderer.DrawWorld(world, mainCamera);

            GLCall(glfwSwapBuffers(window));

            GLCall(glfwPollEvents());
        }
    }

    glfwTerminate();
    return 0;
}