#ifndef OPENGL_BUFFER_HPP
#define OPENGL_BUFFER_HPP

#include <GL/glew.h>

class OpenGL_Buffer
{
protected:
	GLuint _id;
	GLenum _type;

public:
	~OpenGL_Buffer();

	void Construct(GLenum ntype = GL_ARRAY_BUFFER);
	void Bind() const;
	void Unbind() const;
};

#endif

