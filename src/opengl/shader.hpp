#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <GL/glew.h>

#include "../utils.hpp"

class Shader
{
	GLuint _type;
	std::string _source_filename;
	std::string _source_file_contents;

	void compile();
public:
	GLuint id;

	void Create(std::string n_source_filename, GLuint n_type);
	Shader();
	~Shader();
};

#endif


