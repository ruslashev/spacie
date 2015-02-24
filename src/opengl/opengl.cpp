#include "opengl.hpp"

void generatePlanet(std::vector<GLfloat> *vertices,
		std::vector<GLushort> *elements)
{
	static unsigned short element_counter = 0;
	struct v3 {
		float x, y, z;
		unsigned short id;
		v3(float nx, float ny, float nz) {
			x = nx;
			y = ny;
			z = nz;
			id = element_counter++;
			printf("create id %d (%f %f %f)\n", id, x, y, z);
		};
		v3 avg(const v3 &b) const {
			const float nx = (x + b.x)/2;
			const float ny = (y + b.y)/2;
			const float nz = (z + b.z)/2;
			v3 nv(nx, ny, nz);
			nv.normalize();
			return nv;
		}
		v3 operator/(const float &r) { return v3(x/r, y/r, z/r); }
		v3 operator*(const float &r) { return v3(x*r, y*r, z*r); }
		float len() const { return sqrtf(x*x + y*y + z*z); }
		void normalize() {
			const float l = len();
			if ((int)l == 0)
				return;
			x /= l;
			y /= l;
			z /= l;
		}
	};
	struct triangle {
		v3 f, s, t;
		bool dirty;
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

	triangles.push_back({D,A,C, false});
	triangles.push_back({D,C,B, false});
	triangles.push_back({D,A,B, false});
	triangles.push_back({A,B,C, false});

	for (auto &t : triangles) {
		if (t.dirty)
			continue;

		v3 midp_fs = t.f.avg(t.s);
		v3 midp_ft = t.f.avg(t.t);
		v3 midp_st = t.s.avg(t.t);

		triangle new_tri { midp_fs, midp_ft, midp_st, true };

		triangles.push_back(new_tri);
	}
	for (size_t i = 0; i < triangles.size(); i++)
		triangles[i].dirty = false;

	std::vector<GLfloat> lv; // local_vertices
	std::vector<GLushort> le; // local_elements
	std::vector<bool> pushed;
	pushed.resize(triangles.size()*3, 0);
	for (auto &t : triangles) {
		if (!pushed[t.f.id]) {
			pushed[t.f.id] = true;
			lv.push_back(t.f.x);
			lv.push_back(t.f.y);
			lv.push_back(t.f.z);
			le.push_back(t.f.id);
		} else {
			le.push_back(t.f.id);
		}

		if (!pushed[t.s.id]) {
			pushed[t.s.id] = true;
			lv.push_back(t.s.x);
			lv.push_back(t.s.y);
			lv.push_back(t.s.z);
			le.push_back(t.s.id);
		} else {
			le.push_back(t.s.id);
		}

		if (!pushed[t.t.id]) {
			pushed[t.t.id] = true;
			lv.push_back(t.t.x);
			lv.push_back(t.t.y);
			lv.push_back(t.t.z);
			le.push_back(t.t.id);
		} else {
			le.push_back(t.t.id);
		}
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
}

void OpenGL::Update(unsigned int dt, unsigned int t)
{
	shader_program.UseThisProgram();

	float time_mod = (float)t/1000.f;
	_view_mat = glm::lookAt(
			glm::vec3(4*cosf(time_mod), 2, 4*sinf(time_mod)),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0));

	shader_program.UpdateMatrices(_model_mat, _view_mat, _proj_mat);
}

void OpenGL::Draw()
{
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

