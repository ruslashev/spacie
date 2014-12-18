#include "opengl.hpp"

void OpenGL::Construct()
{
	vao.Construct();

	std::vector<double> vertices = {
		 0.0f,  0.5f,
		 0.5f, -0.5f,
		-0.5f, -0.5f
	};

	vertex_buffer.Construct();
	vertex_buffer.Upload(vertices);

	shader_vert.Construct("shader.vs", GL_VERTEX_SHADER);
	shader_frag.Construct("shader.fs", GL_FRAGMENT_SHADER);

	shader_program.Construct(shader_vert, shader_frag);
}

void OpenGL::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

