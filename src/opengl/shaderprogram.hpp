#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include "shader.hpp"
#include "arraybuffer.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram
{
	GLint _color_unif;
	GLint _model_mat_unif;
	GLint _proj_mat_unif;
	GLint _view_mat_unif;

	void link(const Shader *vert, const Shader *frag);
	void bindUniforms();
public:
	GLuint id;

	~ShaderProgram();

	void Construct(const Shader *vert, const Shader *frag);
	void BindAttribute(const ArrayBuffer *buffer, const char *name,
		GLint size, GLenum type, GLboolean normalized, GLsizei stride,
		const GLvoid *ptr);
	void UseThisProgram();
	void UpdateMatrices(const glm::mat4 &model,
			const glm::mat4 &view, const glm::mat4 &proj);
};

#endif


