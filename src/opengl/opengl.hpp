#ifndef OPENGL_HPP
#define OPENGL_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "shader.hpp"
#include "shaderprogram.hpp"
#include "vertexarray.hpp"
#include "arraybuffer.hpp"
#include "elementbuffer.hpp"
#include "../obj_loader.hpp"

class OpenGL
{
	ShaderProgram shader_program;
	Shader shader_vert;
	Shader shader_frag;
	VertexArray vao;
	ArrayBuffer vertex_buffer;
	ArrayBuffer normal_buffer;
	ElementBuffer element_buffer;

	glm::mat4 _model_mat;
	glm::mat4 _view_mat;
	glm::mat4 _proj_mat;

	GLuint temp_elements_size;
public:
	void Construct(const unsigned int window_width, const unsigned int window_height);
	void Draw();
	void Resize(const int new_width, const int new_height);
};

#endif

