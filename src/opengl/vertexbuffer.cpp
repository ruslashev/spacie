#include "vertexbuffer.hpp"

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &id);
}

void VertexBuffer::Upload(std::vector<double> &data)
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(data[0]), data.data(),
			GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &id);
}
