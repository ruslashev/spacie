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

	ShaderProgram(const Shader &vert, const Shader &frag);
	~ShaderProgram();

	void UseThisProgram();
};

#endif


