#include "elementbuffer.hpp"

void ElementBuffer::Upload(std::vector<GLushort> &data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size()*sizeof(data[0]), data.data(),
			GL_STATIC_DRAW);
}

