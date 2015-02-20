#include "opengl.hpp"

void generatePlanet(std::vector<GLfloat> *vertices,
		std::vector<GLushort> *elements)
{
	struct vec3 {
		float x, y, z;
	};
	struct triangle {
		vec3 f, s, t;
	};
	printf("char size    : %lu\n", sizeof(char));
	printf("float size   : %lu\n", sizeof(float));
	printf("vec3 size    : %lu\n", sizeof(vec3));
	printf("triangle size: %lu\n", sizeof(triangle));
	std::vector<triangle> triangles;
	const float a = 5;
	triangles.push_back({
			{ -a/2, 0, -a*sqrtf(3)/6.f},
			{    0, 0,  a*sqrtf(3)/3.f},
			{  a/2, 0, -a*sqrtf(3)/6.f}});
	std::vector<GLfloat> verts;
	std::vector<GLushort> elems;
	elems.push_back(0);
	for (size_t i = 0; i < triangles.size(); i++) {
		verts.push_back(triangles[i].f.x);
		verts.push_back(triangles[i].f.y);
		verts.push_back(triangles[i].f.z);

		verts.push_back(triangles[i].s.x);
		verts.push_back(triangles[i].s.y);
		verts.push_back(triangles[i].s.z);

		verts.push_back(triangles[i].t.x);
		verts.push_back(triangles[i].t.y);
		verts.push_back(triangles[i].t.z);

		elems.push_back(elems.back()+1);
		elems.push_back(elems.back()+1);
		elems.push_back(elems.back()+1);
	}
	elems.pop_back();
	*vertices = verts;
	*elements = elems;
}

void OpenGL::Construct(const unsigned int window_width,
		const unsigned int window_height)
{
	vao.Construct();

	Resize(window_width, window_height);

	std::vector<GLfloat> vertices;
	std::vector<GLushort> elements;
	generatePlanet(&vertices, &elements);

	vertex_buffer.Construct();
	vertex_buffer.Upload(vertices);

	element_buffer.Construct(GL_ELEMENT_ARRAY_BUFFER);
	element_buffer.Upload(elements);
	temp_elements_size = elements.size();

	shader_vert.Construct("shader.vs", GL_VERTEX_SHADER);
	shader_frag.Construct("shader.fs", GL_FRAGMENT_SHADER);

	shader_program.Construct(&shader_vert, &shader_frag);
	shader_program.BindAttribute(&vertex_buffer, "position",
			3, GL_FLOAT, GL_FALSE, 0, 0);

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
	shader_program.UseThisProgram();
	shader_program.UpdateMatrices(_model_mat, _view_mat, _proj_mat);

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	element_buffer.Bind();
	glDrawElements(GL_TRIANGLES, temp_elements_size, GL_UNSIGNED_SHORT, 0);
	element_buffer.Unbind();
	shader_program.DontUseThisProgram();
}

void OpenGL::Resize(const int new_width, const int new_height)
{
	glViewport(0, 0, new_width, new_height);
}

