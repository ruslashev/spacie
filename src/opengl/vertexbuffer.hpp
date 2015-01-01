#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include "opengl_buffer.hpp"

#include <vector>
#include <GL/glew.h>

class VertexBuffer : public OpenGL_Buffer
{
public:
	void Upload(std::vector<GLfloat> &data);
};

#endif

