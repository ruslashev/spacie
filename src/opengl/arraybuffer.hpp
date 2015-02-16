#ifndef ARRAYBUFFER_HPP
#define ARRAYBUFFER_HPP

#include "opengl_buffer.hpp"

#include <vector>
#include <GL/glew.h>

class ArrayBuffer : public OpenGL_Buffer
{
public:
	void Upload(std::vector<GLfloat> &data);
};

#endif

