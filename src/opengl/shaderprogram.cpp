#include "shaderprogram.hpp"

ShaderProgram::ShaderProgram(Shader &vert, Shader &frag)
{
	id = glCreateProgram();
	glAttachShader(id, vert.id);
	glAttachShader(id, frag.id);
	glLinkProgram(id);
}

void ShaderProgram::BindAttributes()
{
	position_attr = glGetAttribLocation(id, "position");
	glVertexAttribPointer(position_attr, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_attr);
}

