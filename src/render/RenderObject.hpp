#ifndef RENDEROBJECT_HPP
#define RENDEROBJECT_HPP

#include "humangl.h"
#include "ftm.hpp"

class RenderObject {
public:

	RenderObject(GLuint vbo, GLuint vao, GLint verts_count, GLuint program, GLint mvp_loc, GLint color_loc, GLint selected_loc);

	void Render(const ftm::mat4 &&mvp) const;
	void RenderColor(const ftm::mat4 &mvp, const ftm::vec3 &color, bool selected) const;

private:
	RenderObject() {};
	RenderObject(const RenderObject &other) {};
	RenderObject & operator=(const RenderObject &other) { return *this; };

	GLuint	_vbo;
	GLuint	_vao;
	GLuint	_program;
	GLint	_verts_count;
	GLint	_mvp_loc;
	GLint	_color_loc;
	GLint	_selected_loc;
};


#endif //RENDEROBJECT_HPP
