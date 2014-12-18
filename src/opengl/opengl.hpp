#ifndef OPENGL_HPP
#define OPENGL_HPP

#include <GL/glew.h>
#include <vector>

#include "shader.hpp"
#include "shaderprogram.hpp"
#include "vertexarray.hpp"
#include "vertexbuffer.hpp"

class OpenGL
{
	ShaderProgram shader_program;
	Shader shader_vert;
	Shader shader_frag;
	VertexArray vao;
	VertexBuffer vertex_buffer;

public:
	void Construct();
	void Draw();
};

#endif

