#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include "shader.hpp"
#include <GL/glew.h>

class ShaderProgram
{
	GLint _position_attr;
	
	void bindAttributes();
public:
	GLuint id;

	~ShaderProgram();

	void Construct(const Shader *vert, const Shader *frag);
	void UseThisProgram();
};

#endif


