#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "RenderObject.hpp"

#include "def.h"
extern GLuint error;

RenderObject::RenderObject(GLuint vbo, GLuint vao, GLint verts_count, GLuint program, GLint mvp_loc)
	: _vbo(vbo), _vao(vao), _program(program), _verts_count(verts_count), _mvp_loc(mvp_loc)
	{}

void RenderObject::Render(const glm::mat4 &&mvp) const {
	GL (glUseProgram(_program));
	glBindVertexArray(_vao);
	GL (glUniformMatrix4fv (_mvp_loc, 1, GL_FALSE, glm::value_ptr(mvp)));
	glDrawArrays (GL_TRIANGLES, 0, _verts_count);
	glBindVertexArray(0);
}