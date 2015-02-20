#include "opengl.hpp"

void generatePlanet(std::vector<GLfloat> *vertices,
		std::vector<GLushort> *elements)
{
	struct v3 {
		float x, y, z;
	};
	struct triangle {
		v3 f, s, t;
	};

	std::vector<triangle> triangles;

	const float a = 3;                // right triangle edge
	const float s = a*sqrtf(3)/6;     // the one third of altitude
	const float b = a*sqrtf(3)/3;     // the two thirds
	const float H = a*sqrtf(2.f/3.f); // height in space

	const v3 D = {    0,  H,  0 };
	const v3 A = { -a/2,  0, -s };
	const v3 B = {    0,  0,  b };
	const v3 C = {  a/2,  0, -s };

	struct lookup_list {
		std::vector<v3> list;
		const size_t operator[](const v3 &k) const {
			for (size_t i = 0; i < list.size(); i++)
				if ((k.x == list[i].x) &&
					(k.y == list[i].y) &&
					(k.z == list[i].z))
					return i;
			return 0;
		}
	};
	lookup_list elem_lookup;
	elem_lookup.list = {D, A, B, C};

	triangles.push_back({D,A,C});
	triangles.push_back({D,C,B});
	triangles.push_back({D,A,B});
	triangles.push_back({A,B,C});

	std::vector<GLfloat> lv; // local_vertices
	std::vector<GLushort> le; // local_elements
	for (size_t i = 0; i < triangles.size(); i++) {
		lv.push_back(triangles[i].f.x);
		lv.push_back(triangles[i].f.y);
		lv.push_back(triangles[i].f.z);

		lv.push_back(triangles[i].s.x);
		lv.push_back(triangles[i].s.y);
		lv.push_back(triangles[i].s.z);

		lv.push_back(triangles[i].t.x);
		lv.push_back(triangles[i].t.y);
		lv.push_back(triangles[i].t.z);

		le.push_back(elem_lookup[triangles[i].f]);
		le.push_back(elem_lookup[triangles[i].s]);
		le.push_back(elem_lookup[triangles[i].t]);
	}
	*vertices = lv;
	*elements = le;
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
			glm::vec3(4, 4, 4),
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
	glDrawElements(GL_LINE_LOOP, temp_elements_size, GL_UNSIGNED_SHORT, 0);
	element_buffer.Unbind();
	shader_program.DontUseThisProgram();
}

void OpenGL::Resize(const int new_width, const int new_height)
{
	glViewport(0, 0, new_width, new_height);
}

