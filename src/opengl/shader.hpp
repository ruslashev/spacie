#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <GL/glew.h>

#include "../utils.hpp"

class Shader
{
	GLuint _type;
	std::string _filename;
	std::string _fileContents;

	void readFile();
	void compile();
public:
	GLuint id;

	void Create(std::string n_filename, GLuint n_type);
	Shader();
	~Shader();
};

#endif


