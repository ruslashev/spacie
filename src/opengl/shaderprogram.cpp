#include "shaderprogram.hpp"

void ShaderProgram::Construct(const Shader &vert, const Shader &frag)
{
	id = glCreateProgram();
	glAttachShader(id, vert.id);
	glAttachShader(id, frag.id);

	bindAttributes();

	glBindFragDataLocation(id, 0, "outColor");

	glLinkProgram(id);

	UseThisProgram();
}

void ShaderProgram::bindAttributes()
{
	_position_attr = glGetAttribLocation(id, "position");
	glEnableVertexAttribArray(_position_attr);
	glVertexAttribPointer(_position_attr, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void ShaderProgram::UseThisProgram()
{
	glUseProgram(id);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(id);
}

