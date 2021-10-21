#ifndef RENDEROBJECT_HPP
#define RENDEROBJECT_HPP

#include "humangl.h"

class RenderObject {
public:	// TODO: add def constructor, copy constructor, assingnation, destructor

	RenderObject(GLuint vbo, GLuint vao, GLint verts_count, GLuint program, GLint mvp_loc, GLint color_loc, GLint selected_loc);

	void Render(const glm::mat4 &&mvp) const;
	void RenderColor(const glm::mat4 &mvp, const glm::vec3 &color, bool selected) const;

private:

	GLuint	_vbo;
	GLuint	_vao;
	GLuint	_program;
	GLint	_verts_count;
	GLint	_mvp_loc;
	GLint	_color_loc;
	GLint	_selected_loc;
};


#endif //RENDEROBJECT_HPP
