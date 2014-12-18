#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include <vector>
#include <GL/glew.h>

class VertexBuffer
{
	GLuint _id;

public:
	VertexBuffer();
	~VertexBuffer();

	void Upload(std::vector<double> &data);
};

#endif

