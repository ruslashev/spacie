#include "shader.hpp"
#include "../utils.hpp"

void Shader::Create(std::string n_filename, GLuint n_type)
{
	_type = n_type;
	_filename = n_filename;

	id = glCreateShader(_type);
	readFile();
	const char *_filename_c_str = _filename.c_str();
	glShaderSource(id, 1, &_filename_c_str, NULL);
	compile();
}

void Shader::readFile()
{
	std::ifstream ifs(_filename.c_str(), std::ifstream::binary);
	assertf(ifs, "Failed to open file \"%s\" for reading.", _filename.c_str());

	ifs.seekg(0, ifs.end);
	const int filesize = ifs.tellg();

	ifs.seekg(0, ifs.beg);

	char *buffer = new char [filesize];

	ifs.read(buffer, filesize);

	assertf(ifs, "Only %d characters (%d%%) read from file \"%s\"",
			ifs.gcount(), 100*ifs.gcount()/(double)filesize, _filename.c_str());
	ifs.close();

	std::string strbuffer(buffer);
	_fileContents = strbuffer;

	delete[] buffer;
}

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

