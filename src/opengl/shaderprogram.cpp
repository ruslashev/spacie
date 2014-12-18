#include "shaderprogram.hpp"

void ShaderProgram::Construct(const Shader &vert, const Shader &frag)
{
	id = glCreateProgram();
	glAttachShader(id, vert.id);
	glAttachShader(id, frag.id);
	glLinkProgram(id);
}

void ShaderProgram::bindAttributes()
{
	_position_attr = glGetAttribLocation(id, "position");
	glVertexAttribPointer(_position_attr, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(_position_attr);
}

void ShaderProgram::UseThisProgram()
{
	glUseProgram(id);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(id);
}

