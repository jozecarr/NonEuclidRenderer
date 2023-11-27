#pragma once

#include <vector>
#include <GL/glew.h>

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	bool normalized;
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		: m_Stride(0) {}

	template<typename T>
	void Push(int count) {
		static_assert(false);
	}

	template<>
	void Push<float>(int count) {
		VertexBufferElement e = { GL_FLOAT, count, false };
		m_Elements.push_back(e);
		m_Stride += sizeof(GLfloat);
	}

	template<>
	void Push<unsigned int>(int count) {
		VertexBufferElement e = { GL_UNSIGNED_INT, count, false };
		m_Elements.push_back(e);
		m_Stride += sizeof(GLuint);
	}

	template<>
	void Push<unsigned char>(int count) {
		VertexBufferElement e = { GL_UNSIGNED_BYTE, count, true };
		m_Elements.push_back(e);
		m_Stride += sizeof(GLbyte);  
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};