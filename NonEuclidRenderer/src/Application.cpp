#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
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

//settings

const unsigned int SCR_WIDTH = 2000;
const unsigned int SCR_HEIGHT = 2000;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
Input input(true, SCR_WIDTH / 2.0f, SCR_HEIGHT / 2.0);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main(void){
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "NON-EUCLIDEAN PROJ", NULL, NULL);
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
        input.mouse_callback(win, xpos, ypos, camera);
        });

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glewInit() != GLEW_OK)
        std::cout << "glewInit fail" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);

    {
        
        float vertices[8 * 5] = {
            -1, -1, -1, 0, 0,
             1, -1, -1, 1, 0,
             1,  1, -1, 1, 1,
            -1,  1, -1, 0, 1,
            -1, -1,  1, 0, 0,
             1, -1,  1, 1, 0,
             1,  1,  1, 1, 1,
            -1,  1,  1, 0, 1
        };

        unsigned int indices[6 * 6] =
        {
            0, 1, 3, 3, 1, 2,
            1, 5, 2, 2, 5, 6,
            5, 4, 6, 6, 4, 7,
            4, 0, 7, 7, 0, 3,
            3, 2, 7, 7, 2, 6,
            4, 5, 0, 0, 5, 1
        };


        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(vertices, 6 * 6 * 5 * sizeof(float));
        
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout); 

        IndexBuffer ib(indices, 6 * 6);
        
        Shader shader("res/shaders/Basic.shader");
        shader.Bind();

        Texture texture("res/textures/smile.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        printf("%s\n", glGetString(GL_VERSION));

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            input.ProcessInput(window, camera, deltaTime);

            /* Render here */
            renderer.Clear();

            shader.Bind();

            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 
                (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            shader.SetUniformMat4("projection", projection);

            glm::mat4 view = camera.GetViewMatrix();
            shader.SetUniformMat4("view", view);

            va.Bind();
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0,0,0));
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.SetUniformMat4("model", model);

            //for (unsigned int i = 0; i < 10; i++)
            //{
            //    // calculate the model matrix for each object and pass it to shader before drawing
            //    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            //    model = glm::translate(model, cubePositions[i]);
            //    float angle = 20.0f * i;
            //    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            //    shader.SetUniformMat4("model", model);

            //    glDrawArrays(GL_TRIANGLES, 0, 36);
            //}

            renderer.Draw(va, ib, shader);

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }
    }

    glfwTerminate();
    return 0;
}