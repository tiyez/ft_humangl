#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "RenderObject.hpp"

#include "def.h"
extern GLuint error;

RenderObject::RenderObject(GLuint vbo, GLuint vao, GLint verts_count, GLuint program, GLint mvp_loc, GLint color_loc, GLint selected_loc)
	: _vbo(vbo), _vao(vao), _program(program), _verts_count(verts_count), _mvp_loc(mvp_loc), _color_loc(color_loc), _selected_loc(selected_loc)
	{}

void RenderObject::Render(const ftm::mat4 &&mvp) const {
	GL (glUseProgram(_program));
	glBindVertexArray(_vao);
	GL (glUniformMatrix4fv (_mvp_loc, 1, GL_FALSE, (float*)&mvp.r0));
	glDrawArrays (GL_TRIANGLES, 0, _verts_count);
	glBindVertexArray(0);
}

void RenderObject::RenderColor(const ftm::mat4 &mvp, const ftm::vec3 &color, bool selected) const {
	GL (glUseProgram(_program));
	glBindVertexArray(_vao);
	GL (glUniform3fv (_color_loc, 1, &color.x));
	GL (glUniformMatrix4fv (_mvp_loc, 1, GL_FALSE, &mvp.r0.x));
	GL (glUniform1i(_selected_loc, selected));
	glDrawArrays (GL_TRIANGLES, 0, _verts_count);
	glBindVertexArray(0);
}
