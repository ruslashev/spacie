#include "shader.hpp"

void Shader::compile()
{
	glCompileShader(id);

	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {
		char buffer[512];
		glGetShaderInfoLog(id, 512, NULL, buffer);
		errorf("Failed to compile %s shader:\n%s",
				_type == GL_VERTEX_SHADER ? "Vertex" : "Fragment",
				buffer);
	}
}

void Shader::Create(std::string n_source_filename, GLuint n_type)
{
	_source_filename = n_source_filename;
	_type = n_type;

	id = glCreateShader(_type);

	_source_file_contents = readFile(_source_filename);

	const char *source_c_str = _source_file_contents.c_str();
	glShaderSource(id, 1, &source_c_str, NULL);

	compile();
}

