#include "opengl.hpp"

void generatePlanet(std::vector<GLfloat> *vertices,
		std::vector<GLushort> *elements)
{
	struct v3 {
		float x, y, z;
		v3(float nx, float ny, float nz) {
			x = nx;
			y = ny;
			z = nz;
		};
		v3 avg(const v3 &b) const {
			const float nx = (x + b.x)/2;
			const float ny = (y + b.y)/2;
			const float nz = (z + b.z)/2;
			v3 nv(nx, ny, nz);
			// nv.normalize();
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
		unsigned int f, s, t;
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

	std::vector<v3> used_vertices;
	used_vertices.push_back(D);
	used_vertices.push_back(A);
	used_vertices.push_back(B);
	used_vertices.push_back(C);

	triangles.push_back({0,1,3, false});
	triangles.push_back({0,3,2, false});
	triangles.push_back({0,1,2, false});
	triangles.push_back({1,2,3, false});

	const size_t triangles_len = triangles.size();
	for (size_t i = 0; i < triangles_len; i++) {
		const triangle t = triangles[i];
		if (t.dirty)
			continue;

		// if you want to understand the code below,
		// grab a pen & paper

		const unsigned int f_i = t.f;
		const unsigned int s_i = t.s;
		const unsigned int t_i = t.t;

		v3 f_v = used_vertices[f_i];
		v3 s_v = used_vertices[s_i];
		v3 t_v = used_vertices[t_i];

		const v3 midp_fs = f_v.avg(s_v);
		const v3 midp_ft = f_v.avg(t_v);
		const v3 midp_st = s_v.avg(t_v);

		used_vertices.push_back(midp_fs);
		const unsigned int fs_i = used_vertices.size()-1;
		used_vertices.push_back(midp_ft);
		const unsigned int ft_i = used_vertices.size()-1;
		used_vertices.push_back(midp_st);
		const unsigned int st_i = used_vertices.size()-1;

		triangle new_f_ft_fs { f_i, ft_i, fs_i, true };
		triangle new_s_fs_st { s_i, fs_i, st_i, true };
		triangle new_t_st_ft { t_i, st_i, ft_i, true };
		triangle new_fs_st_ft { fs_i, st_i, ft_i, true };

		// todo: is dirty even needed?
		triangles.erase(triangles.begin()+i);
		triangles.insert(triangles.begin()+i, new_f_ft_fs);
		triangles.insert(triangles.begin()+i, new_s_fs_st);
		triangles.insert(triangles.begin()+i, new_t_st_ft);
		triangles.insert(triangles.begin()+i, new_fs_st_ft);
		i += 4;
		i--; // because of the increment in for loop
	}
	for (size_t i = 0; i < triangles.size(); i++)
		triangles[i].dirty = false;

	std::vector<GLfloat> local_vertices;
	std::vector<GLushort> local_elements;
	for (auto &v : used_vertices) {
		local_vertices.push_back(v.x);
		local_vertices.push_back(v.y);
		local_vertices.push_back(v.z);
	}
	for (auto &t : triangles) {
		local_elements.push_back(t.f);
		local_elements.push_back(t.s);
		local_elements.push_back(t.t);
	}

	*vertices = local_vertices;
	*elements = local_elements;
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
	glDrawElements(GL_POINTS, temp_elements_size, GL_UNSIGNED_SHORT, 0);
	element_buffer.Unbind();
	shader_program.DontUseThisProgram();
}

void OpenGL::Resize(const int new_width, const int new_height)
{
	glViewport(0, 0, new_width, new_height);
}

