#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include <vector>
#include <GL/glew.h>

class VertexBuffer
{
	GLuint id;

public:
	VertexBuffer();
	void Upload(std::vector<double> &data);
	~VertexBuffer();
};

#endif

