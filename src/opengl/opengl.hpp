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
#include "vertexbuffer.hpp"

class OpenGL
{
	ShaderProgram shader_program;
	Shader shader_vert;
	Shader shader_frag;
	VertexArray vao;
	VertexBuffer vertex_buffer;

	glm::mat4 _model_mat;
	glm::mat4 _view_mat;
	glm::mat4 _proj_mat;
public:
	void Construct(const unsigned int window_width, const unsigned int window_height);
	void Draw();
};

#endif

