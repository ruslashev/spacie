#ifndef OPENGL_BUFFER_HPP
#define OPENGL_BUFFER_HPP

#include <GL/glew.h>

class OpenGL_Buffer
{
protected:
	GLuint _id;

public:
	~OpenGL_Buffer();

	void Construct();
};

#endif


