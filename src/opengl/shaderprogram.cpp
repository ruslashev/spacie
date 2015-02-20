#include "shaderprogram.hpp"

void ShaderProgram::Construct(const Shader *vert, const Shader *frag)
{
	id = glCreateProgram();
	link(vert, frag);

	UseThisProgram();
	glBindFragDataLocation(id, 0, "outColor");
	bindUniforms();
}

void ShaderProgram::link(const Shader *vert, const Shader *frag)
{
	glAttachShader(id, vert->id);
	glAttachShader(id, frag->id);

	glLinkProgram(id);

	GLint status = GL_FALSE;
	glGetProgramiv(id, GL_LINK_STATUS, &status);

	if (status == GL_FALSE) {
		char buffer[1024];
		glGetProgramInfoLog(id, 1024, NULL, buffer);

		std::string buf_str(buffer);
		// strip trailing newline
		buf_str.pop_back();
		// indent every line
		int indent = 5;
		buf_str.insert(buf_str.begin(), indent, ' ');
		for (size_t i = 0; i < buf_str.size(); i++) {
			if (buf_str[i] != '\n')
				continue;
			buf_str.insert(i, indent, ' ');
		}

		glDetachShader(id, vert->id);
		glDetachShader(id, frag->id);

		errorf("Failed to link shaders:\n%s",
				buf_str.c_str());
	}
}

void ShaderProgram::bindUniforms()
{
	_color_unif = glGetUniformLocation(id, "triangleColor");
	glUniform3f(_color_unif, 0.0f, 1.0f, 0.0f);

	_model_mat_unif = glGetUniformLocation(id, "model");
	_proj_mat_unif = glGetUniformLocation(id, "proj");
	_view_mat_unif = glGetUniformLocation(id, "view");
}

void ShaderProgram::BindAttribute(const ArrayBuffer *buffer, const char *name,
		GLint size, GLenum type, GLboolean normalized, GLsizei stride,
		const GLvoid *ptr)
{
	buffer->Bind();
	GLint attr = glGetAttribLocation(id, name);
	glEnableVertexAttribArray(attr);
	glVertexAttribPointer(attr, size, type, normalized, stride, ptr);
	buffer->Unbind();
}

void ShaderProgram::UseThisProgram()
{
	glUseProgram(id);
}

void ShaderProgram::DontUseThisProgram()
{
	glUseProgram(0);
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

