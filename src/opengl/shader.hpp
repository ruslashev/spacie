#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <GL/glew.h>

class Shader
{
	std::string file;
	void ReadFile(std::string filename);
public:
	Shader(std::string filename);
	~Shader();
};

#endif


