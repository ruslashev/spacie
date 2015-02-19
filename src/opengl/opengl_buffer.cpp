#include "opengl_buffer.hpp"

void OpenGL_Buffer::Construct(GLenum ntype)
{
	_type = ntype;
	glGenBuffers(1, &_id);
}

OpenGL_Buffer::~OpenGL_Buffer()
{
	glDeleteBuffers(1, &_id);
}

void OpenGL_Buffer::Bind() const
{
	glBindBuffer(_type, _id);
}

void OpenGL_Buffer::Unbind() const
{
	glBindBuffer(_type, 0);
}

