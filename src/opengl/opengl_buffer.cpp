#include "opengl_buffer.hpp"

void OpenGL_Buffer::Construct()
{
	glGenBuffers(1, &_id);
}

OpenGL_Buffer::~OpenGL_Buffer()
{
	glDeleteBuffers(1, &_id);
}

