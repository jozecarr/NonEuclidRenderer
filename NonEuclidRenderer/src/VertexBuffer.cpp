#include "VertexBuffer.h"

#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    GLCall(glGenBuffers(1, &rendererID)); //tell opengl to generate a buffer at "buffer"
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID)); //bind that buffer to opengl
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); //tell the buffer what data to use
}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &rendererID));
}

void VertexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID)); //bind that buffer to opengl
}

void VertexBuffer::Unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); //bind that buffer to opengl
}