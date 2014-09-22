#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include "shader.hpp"
#include <GL/glew.h>

class ShaderProgram
{
	GLint position_attr;
	
	void BindAttributes();
public:
	GLuint id;

	ShaderProgram(Shader &vert, Shader &frag);
	~ShaderProgram();

	void UseThisProgram();
};

#endif


