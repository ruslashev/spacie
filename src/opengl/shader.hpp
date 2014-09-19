#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <GL/glew.h>

class Shader
{
    GLuint id;
    GLuint type;
	std::string file;

	void ReadFile(std::string filename);
    void Compile();
public:
	Shader(std::string filename, GLuint type);
	~Shader();
};

#endif


