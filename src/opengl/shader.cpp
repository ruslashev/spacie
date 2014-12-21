#include "shader.hpp"

void Shader::Construct(const std::string n_source_filename, GLuint n_type)
{
	_source_filename = n_source_filename;
	_type = n_type;

	id = glCreateShader(_type);

	_source_file_contents = readFile(_source_filename);

	const char *source_c_str = _source_file_contents.c_str();
	glShaderSource(id, 1, &source_c_str, NULL);

	compile();
}

void Shader::compile()
{
	glCompileShader(id);

	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {
		char buffer[512];
		glGetShaderInfoLog(id, 512, NULL, buffer);

		std::string buf_str(buffer);
		// strip trailing newline
		buf_str.pop_back();
		// indent error log
		int indent = 5;
		buf_str.insert(buf_str.begin(), indent, ' ');
		for (size_t i = 0; i < buf_str.size(); i++) {
			if (buf_str[i] != '\n')
				continue;
			buf_str.insert(i, indent, ' ');
		}

		errorf("Failed to compile %s shader:\n%s",
				_type == GL_VERTEX_SHADER ? "Vertex" : "Fragment",
				buf_str.c_str());
	}
}

Shader::~Shader()
{
	glDeleteShader(id);
}

