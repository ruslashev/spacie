#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include <vector>
#include <GL/glew.h>

class VertexBuffer
{
	GLuint _id;

public:
	~VertexBuffer();

	void Construct();
	void Upload(std::vector<float> &data);
};

#endif

