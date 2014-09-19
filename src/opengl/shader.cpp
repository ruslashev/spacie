#include "shader.hpp"
#include "../utils.hpp"

Shader::Shader(std::string filename, GLuint n_type)
{
	type = n_type;
	id = glCreateShader(type);
	ReadFile(filename);
	const char *file_c_str = file.c_str();
	glShaderSource(id, 1, &file_c_str, NULL);
	Compile();
}

void Shader::ReadFile(std::string filename)
{
	std::ifstream ifs(filename.c_str(), std::ifstream::binary);
	assertf(ifs, "Failed to open file \"%s\" for reading.", filename.c_str());

	ifs.seekg(0, ifs.end);
	int filesize = ifs.tellg();

	ifs.seekg(0, ifs.beg);

	char *buffer = new char [filesize];

	ifs.read(buffer, filesize);

	assertf(ifs, "Only %d characters (%d%%) read from file \"%s\"",
			ifs.gcount(), 100*ifs.gcount()/(double)filesize, filename.c_str());
	ifs.close();

	std::string strbuffer(buffer);
	file = strbuffer;

	delete[] buffer;
}

void Shader::Compile()
{
	glCompileShader(id);

	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		char buffer[512];
		glGetShaderInfoLog(id, 512, NULL, buffer);
		errorf("Failed to compile %s shader:\n%s",
				type == GL_VERTEX_SHADER ? "Vertex" : "Fragment",
				buffer);
	}
}

