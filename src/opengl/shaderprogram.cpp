#include "shaderprogram.hpp"

void ShaderProgram::Construct(const Shader *vert, const Shader *frag)
{
	id = glCreateProgram();
	glAttachShader(id, vert->id);
	glAttachShader(id, frag->id);
	glBindFragDataLocation(id, 0, "outColor");
	glLinkProgram(id);
	UseThisProgram();

	bindUniforms();
}

void ShaderProgram::BindAttributes(const ArrayBuffer *vertex_buffer,
		const ArrayBuffer *normal_buffer)
{
	vertex_buffer->Bind();
	_position_attr = glGetAttribLocation(id, "position");
	glEnableVertexAttribArray(_position_attr);
	glVertexAttribPointer(_position_attr, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDisableVertexAttribArray(_position_attr);
	vertex_buffer->Unbind();

	normal_buffer->Bind();
	_normal_attr = glGetAttribLocation(id, "normal");
	glEnableVertexAttribArray(_normal_attr);
	glVertexAttribPointer(_normal_attr, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDisableVertexAttribArray(_normal_attr);
	normal_buffer->Unbind();
}

void ShaderProgram::bindUniforms()
{
	_color_unif = glGetUniformLocation(id, "triangleColor");
	glUniform3f(_color_unif, 0.0f, 1.0f, 0.0f);

	_model_mat_unif = glGetUniformLocation(id, "model");
	_proj_mat_unif = glGetUniformLocation(id, "proj");
	_view_mat_unif = glGetUniformLocation(id, "view");
}

void ShaderProgram::UseThisProgram()
{
	glUseProgram(id);
}

void ShaderProgram::UpdateMatrices(const glm::mat4 &model,
		const glm::mat4 &view, const glm::mat4 &proj)
{
	glUniformMatrix4fv(_model_mat_unif, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(_view_mat_unif, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(_proj_mat_unif, 1, GL_FALSE, glm::value_ptr(proj));
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(id);
}

