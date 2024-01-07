#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "World.h"
#include "Camera.h"

#define ASSERT(x) if(!(x)) __debugbreak(); 
#define GLCall(x) GLClearError;\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__)) 

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
void framebuffer_size_callback(GLFWwindow * window, int width, int height);

class Renderer {
public:
    void Clear() const;
    void Draw(VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};

void DrawWorld(World& world, Camera& camera, Shader& shader);