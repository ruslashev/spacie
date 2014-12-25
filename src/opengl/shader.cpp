#include "shader.hpp"

void Shader::Construct(std::string n_source_filename, GLuint n_type)
{
	_source_filename = n_source_filename;
	_type = n_type;
	debug_shader_type_str =
				_type == GL_VERTEX_SHADER ? "Vertex" : "Fragment";

	id = glCreateShader(_type);

	source();

	compile();
}

void Shader::source()
{
	std::string source_file_contents = readFile(_source_filename);

	// size sanity check
	const size_t size_sane = 1024;
	if (source_file_contents.size() > size_sane)
		errorf("%s shader (\"%s\") source file is too big: %d bytes out of %d\n"
				"currently being maximum allocated size for a shader.",
				debug_shader_type_str.c_str(),
				_source_filename.c_str(),
				source_file_contents.size(),
				size_sane);

	const size_t len = source_file_contents.size() + 1;
    char *c_str = new char[len];
    memcpy(c_str, source_file_contents.c_str(), len);

	glShaderSource(id, 1, &c_str, NULL);

	delete [] c_str;
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
		// indent every line
		int indent = 5;
		buf_str.insert(buf_str.begin(), indent, ' ');
		for (size_t i = 0; i < buf_str.size(); i++) {
			if (buf_str[i] != '\n')
				continue;
			buf_str.insert(i, indent, ' ');
		}

		errorf("Failed to compile %s shader (\"%s\"):\n%s",
				_type == GL_VERTEX_SHADER ? "Vertex" : "Fragment",
				_source_filename.c_str(),
				buf_str.c_str());
	}
}

Shader::~Shader()
{
	glDeleteShader(id);
}

