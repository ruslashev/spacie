#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <GL/glew.h>

class Shader
{
	GLuint type;
	std::string filename;
	std::string file_contents;

	void ReadFile(std::string filename);
	void Compile();
public:
	GLuint id;

	void Create(std::string n_filename, GLuint n_type);
	Shader();
	~Shader();
};

#endif


