#include "opengl.hpp"
#include "../obj_loader.hpp"

void OpenGL::Construct(const unsigned int window_width, const unsigned int window_height)
{
	vao.Construct();

	std::vector<GLfloat> vertices = LoadOBJ("suzanne.obj");
	vertex_buffer.Construct();
	vertex_buffer.Upload(vertices);

	shader_vert.Construct("shader.vs", GL_VERTEX_SHADER);
	shader_frag.Construct("shader.fs", GL_FRAGMENT_SHADER);

	shader_program.Construct(&shader_vert, &shader_frag);

	_model_mat = glm::mat4();

	float aspect_ratio = (float)window_width/(float)window_height;
	_proj_mat = glm::perspective(45.0f, aspect_ratio, 1.0f, 20.0f);

	_view_mat = glm::lookAt(
			glm::vec3(0, 4, 4),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0));
}

void OpenGL::Draw()
{
	shader_program.UpdateMatrices(_model_mat, _view_mat, _proj_mat);

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 508);
}

