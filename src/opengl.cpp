#include "opengl.hpp"
#include "utils.hpp"

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &id);
}

void VertexBuffer::Upload(std::vector<double> &data)
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(data[0]), data.data(),
			GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &id);
}

void Shader::ReadFile(std::string filename)
{
	std::ifstream ifs(filename.c_str(), std::ifstream::binary);
	assertf(ifs, "Failed to open file \"%s\" for reading.", filename.c_str());

	ifs.seekg(0, ifs.end);
	int filesize = ifs.tellg();

	ifs.seekg(0, ifs.beg);

	char *buffer = new char [filesize];

	ifs.read(buffer, filesize);

	assertf(ifs, "Only %d characters (%d%%) read from file \"%s\"",
			ifs.gcount(), 100*ifs.gcount()/(double)filesize, filename.c_str());
	ifs.close();

	std::string strbuffer(buffer);
	file = strbuffer;

	delete[] buffer;
}

