#include "Renderer.h"

#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function <<
            " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const {
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Renderer::DrawWorld(World &world, Camera& camera) {

    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
        (float)camera.screenWidth / (float)camera.screenHeight, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();

    for (const auto& obj : world.objects)
    {
        obj->shader->Bind();
        obj->shader->SetUniformMat4("view", view);
        obj->shader->SetUniformMat4("projection", projection);
        obj->shader->SetUniformMat4("model", obj->model);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        obj->shader->Unbind();
    }
}