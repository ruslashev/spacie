#include "vertexbuffer.hpp"

void VertexBuffer::Construct()
{
	glGenBuffers(1, &_id);
}

void VertexBuffer::Upload(std::vector<float> &data)
{
	glBindBuffer(GL_ARRAY_BUFFER, _id);
	glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(data[0]), data.data(),
			GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &_id);
}

