#ifndef ELEMENTBUFFER_HPP
#define ELEMENTBUFFER_HPP

#include "opengl_buffer.hpp"

#include <vector>
#include <GL/glew.h>

class ElementBuffer : public OpenGL_Buffer
{
public:
	void Upload(std::vector<GLushort> &data);
};

#endif

