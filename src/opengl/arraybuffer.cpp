#include "arraybuffer.hpp"

void ArrayBuffer::Upload(std::vector<GLfloat> &data)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER,
			data.size()*sizeof(data[0]),
			data.data(),
			GL_STATIC_DRAW);
	Unbind();
}

