#include "opengl.hpp"

void OpenGL::Construct(const unsigned int window_width, const unsigned int window_height)
{
	vao.Construct();

	Resize(window_width, window_height);

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLushort> elements;
	LoadOBJ("suzanne.obj", &vertices, &normals, &elements);

	vertex_buffer.Construct();
	vertex_buffer.Upload(vertices);

	normal_buffer.Construct();
	normal_buffer.Upload(normals);

	element_buffer.Construct(GL_ELEMENT_ARRAY_BUFFER);
	element_buffer.Upload(elements);
	temp_elements_size = elements.size();

	shader_vert.Construct("shader.vs", GL_VERTEX_SHADER);
	shader_frag.Construct("shader.fs", GL_FRAGMENT_SHADER);
	
	shader_program.Construct(&shader_vert, &shader_frag);
	shader_program.BindAttributes(&vertex_buffer, &normal_buffer);

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
	glDrawElements(GL_TRIANGLES, temp_elements_size, GL_UNSIGNED_SHORT, 0);
}

void OpenGL::Resize(const int new_width, const int new_height)
{
	glViewport(0, 0, new_width, new_height);
}

