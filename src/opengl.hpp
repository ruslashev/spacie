#ifndef OPENGL_HPP
#define OPENGL_HPP

#include <vector>
#include <string>
#include <fstream>
#include <GL/glew.h>

class OpenGL
{

};

class VertexBuffer
{
	GLuint id;

public:
	VertexBuffer();
	void Upload(std::vector<double> &data);
	~VertexBuffer();
};

class Shader
{
	std::string file;
	void ReadFile(std::string filename);
public:
	Shader(std::string filename);
	~Shader();
};

#endif

