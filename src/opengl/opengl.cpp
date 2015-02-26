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
			nv.normalize();
			return nv;
		}
		v3 operator/(const float &r) { return v3(x/r, y/r, z/r); }
		v3 operator*(const float &r) { return v3(x*r, y*r, z*r); }
		float len() const { return sqrtf(x*x + y*y + z*z); }
		void normalize() {
			const float l = len();
			if (std::abs(l) < 0.0000001)
				return;
			x /= l;
			y /= l;
			z /= l;
		}
	};
	struct triangle {
		unsigned int f, s, t;
	};

	std::vector<triangle> triangles;

	const float a = 2;                // edge
	const float phi = (1+sqrtf(5))/2; // golden ratio

	const v3 A_v   = {    0,    1,  phi };
	const v3 B_v   = {    1,  phi,    0 };
	const v3 C_v   = {  phi,    0,    1 };
	const v3 Ay_v  = {    0,   -1,  phi };
	const v3 Az_v  = {    0,    1, -phi };
	const v3 Ayz_v = {    0,   -1, -phi };
	const v3 Bx_v  = {   -1,  phi,    0 };
	const v3 By_v  = {    1, -phi,    0 };
	const v3 Bxy_v = {   -1, -phi,    0 };
	const v3 Cx_v  = { -phi,    0,    1 };
	const v3 Cz_v  = {  phi,    0,   -1 };
	const v3 Cxz_v = { -phi,    0,   -1 };

	const unsigned int A   =  0;
	const unsigned int B   =  1;
	const unsigned int C   =  2;
	const unsigned int Ay  =  3;
	const unsigned int Az  =  4;
	const unsigned int Ayz =  5;
	const unsigned int Bx  =  6;
	const unsigned int By  =  7;
	const unsigned int Bxy =  8;
	const unsigned int Cx  =  9;
	const unsigned int Cz  = 10;
	const unsigned int Cxz = 11;

	std::vector<v3> used_vertices { A_v, B_v, C_v, Ay_v, Az_v, Ayz_v,
		Bx_v, By_v, Bxy_v, Cx_v, Cz_v, Cxz_v };

	for (auto &v : used_vertices)
		v.normalize();

	triangles.push_back({B  , Bx , A  });
	triangles.push_back({B  , Bx , Az });
	triangles.push_back({By , Bxy, Ay });
	triangles.push_back({By , Bxy, Ayz});

	triangles.push_back({A  , Ay , C  });
	triangles.push_back({A  , Ay , Cx });
	triangles.push_back({Az , Ayz, Cz });
	triangles.push_back({Az , Ayz, Cxz});

	triangles.push_back({C  , Cz , B  });
	triangles.push_back({C  , Cz , By });
	triangles.push_back({Cx , Cxz, Bx });
	triangles.push_back({Cx , Cxz, Bxy});

	triangles.push_back({B  , A  , C  });
	triangles.push_back({B  , Az , Cz });
	triangles.push_back({Bx , A  , Cx });
	triangles.push_back({Bx , Az , Cxz});
	triangles.push_back({Bxy, Ay , Cx });
	triangles.push_back({Bxy, Ayz, Cxz});
	triangles.push_back({By , Ay , C  });
	triangles.push_back({By , Ayz, Cz });

	for (int d = 0; d < 3; d++) {
		for (size_t i = triangles.size(); i-- > 0; ) {
			const triangle t = triangles[i];

			// if you want to understand the code below,
			// grab a pen & paper ;)

			const unsigned int f_i = t.f;
			const unsigned int s_i = t.s;
			const unsigned int t_i = t.t;

			const v3 f_v = used_vertices[f_i];
			const v3 s_v = used_vertices[s_i];
			const v3 t_v = used_vertices[t_i];

			const v3 midp_fs = f_v.avg(s_v);
			const v3 midp_ft = f_v.avg(t_v);
			const v3 midp_st = s_v.avg(t_v);

			used_vertices.push_back(midp_fs);
			const unsigned int fs_i = used_vertices.size()-1;
			used_vertices.push_back(midp_ft);
			const unsigned int ft_i = used_vertices.size()-1;
			used_vertices.push_back(midp_st);
			const unsigned int st_i = used_vertices.size()-1;

			const triangle new_f_ft_fs { f_i, ft_i, fs_i };
			const triangle new_s_fs_st { s_i, fs_i, st_i };
			const triangle new_t_st_ft { t_i, st_i, ft_i };
			const triangle new_fs_st_ft { fs_i, st_i, ft_i };

			triangles.erase(triangles.begin()+i);
			triangles.push_back(new_f_ft_fs);
			triangles.push_back(new_s_fs_st);
			triangles.push_back(new_t_st_ft);
			triangles.push_back(new_fs_st_ft);
		}
	}

	for (auto &v : used_vertices) {
		v = v*(a+(rand() % 100)/200.f);
	}

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
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0));

	shader_program.UpdateMatrices(_model_mat, _view_mat, _proj_mat);
}

void OpenGL::Draw()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	element_buffer.Bind();
	glDrawElements(GL_TRIANGLES, temp_elements_size, GL_UNSIGNED_SHORT, 0);
	element_buffer.Unbind();
	shader_program.DontUseThisProgram();
}

void OpenGL::Resize(const int new_width, const int new_height)
{
	glViewport(0, 0, new_width, new_height);
}

