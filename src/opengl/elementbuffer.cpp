#include "elementbuffer.hpp"

void ElementBuffer::Upload(std::vector<GLushort> &data)
{
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size()*sizeof(data[0]), data.data(),
			GL_STATIC_DRAW);
	Unbind();
}

