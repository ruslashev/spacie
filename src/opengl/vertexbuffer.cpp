#include "vertexbuffer.hpp"

void VertexBuffer::Upload(std::vector<GLfloat> &data)
{
	glBindBuffer(GL_ARRAY_BUFFER, _id);
	glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(data[0]), data.data(),
			GL_STATIC_DRAW);
}

