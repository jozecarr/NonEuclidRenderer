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
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "InputCallbacks.h"
#include "GameObject.h"
#include "World.h"
#include "Time.h"
//#include "Raycasting.h"
#include "Collision.h"

#include "Demo.h"

//settings

const unsigned int SCREEN_WIDTH = 2000;
const unsigned int SCREEN_HEIGHT = 2000;

Camera mainCamera(vec3(4.5f, 10.0f, 14.0f));
Camera secondaryCamera(vec3(10.0f, 10.0f, -5.0f));
Camera* cameras[2] = { &mainCamera, &secondaryCamera };

Input input(true, SCR_WIDTH / 2.0f, SCR_HEIGHT / 2.0);

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
    mainCamera.ScreenWidth = SCREEN_WIDTH;
    mainCamera.ScreenHeight = SCREEN_HEIGHT;
    secondaryCamera.ScreenWidth = SCREEN_WIDTH;
    secondaryCamera.ScreenHeight = SCREEN_HEIGHT;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

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

    // set input callbacks, use lambda functions for input classes funcs
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, [](GLFWwindow* win, double xpos, double ypos) {
        input.mouse_callback(win, xpos, ypos, mainCamera);
        });

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

        Texture texture("res/textures/checks_HD.png");
        texture.Bind(1);

        va.Unbind();
        vb.Unbind();
        //ib.Unbind();

        Renderer renderer;

        Time time;
        time.LimitFrameRate(60);

        printf("%s\n", glGetString(GL_VERSION));

        World world = World();
        
        //initialise demo
        Demo demo(&time, &world);

        /////////////////////////////////

        Shader* newShader = new Shader("res/shaders/Basic.shader");
        newShader->Bind();
        newShader->SetUniform1i("u_Texture", 1);
        newShader->SetUniform4f("u_Color", 1.0, 1.0, 1.0, 1.0);
        newShader->Unbind();

        Shader* newShader2 = new Shader("res/shaders/Basic.shader");
        newShader2->Bind();
        newShader2->SetUniform1i("u_Texture", 1);
        newShader2->SetUniform4f("u_Color", 0.0, 1.0, 0.0, 1.0);
        newShader2->Unbind();

        Object* newObj = new Object(newShader, { 4, 2, 1 }, { 5, 8, 0 }, { 0, 0, 10 });
        world.objects.push_back(newObj);
        Object* newObj2 = new Object(newShader2, { 4, 2, 1 }, { 3, 8, 0 }, { 0, 0, 30 });
        world.objects.push_back(newObj2);

        newObj2->Translate({0, 3, 0});

        Object* axisX = new Object(world.objects[0]->shader, { 1000, 0.01, 0.01 }, { 0,0,0 });
        world.AddObject(axisX);
        Object* axisY = new Object(world.objects[0]->shader, { 0.01, 1000, 0.01 }, { 0,0,0 });
        world.AddObject(axisY);
        Object* axisZ = new Object(world.objects[0]->shader, { 0.01, 0.01, 1000 }, { 0,0,0 });
        world.AddObject(axisZ);

        /////////////////////////////////

        //main loop
        while (!glfwWindowShouldClose(window))
        {
            time.Update();
            input.ProcessInput(window, mainCamera, time.GetDeltaTime());

            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

            va.Bind();

            newObj->Rotate({ 0, 0.05, -0.05 });
            newObj2->Rotate({ 0.05, -0.05, 0 });

            cout << (AreObjsColliding(*newObj, *newObj2) ? "colliding\n":"");

            //demo.run();

            renderer.DrawWorld(world, mainCamera);

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }
    }

    glfwTerminate();
    return 0;
}