#pragma once

#include <vector>
#include <GL/glew.h>
#include <stdexcept>
#include "Renderer.h"

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:  return 1;
		}

		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride;
public:
	VertexBufferLayout()
		: stride(0) {}

	template<typename T>
	void Push(unsigned int count) {
		std::runtime_error(false);
	}

	template<>
	void Push<float>(unsigned int count) {
		VertexBufferElement el = { GL_FLOAT, count, GL_FALSE };
		elements.push_back(el);
		stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count) {
		VertexBufferElement el = { GL_UNSIGNED_INT, count, GL_FALSE };
		elements.push_back(el);
		stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		VertexBufferElement e = { GL_UNSIGNED_BYTE, count, GL_TRUE };
		elements.push_back(e);
		stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return elements; }
	inline unsigned int GetStride() const { return stride; }
};