#ifndef RENDEROBJECT_HPP
#define RENDEROBJECT_HPP

#include "humangl.h"

class RenderObject {
public:	// TODO: make normal class (def constructor, copy constructor, assingnation, destructor)

	RenderObject(GLuint vbo, GLuint vao, GLint verts_count, GLuint program, GLint mvp_loc);

	void Render(const glm::mat4 &&vp) const;

private:

	GLuint	_vbo;
	GLuint	_vao;
	GLuint	_program;
	GLint	_verts_count;
	GLint	_mvp_loc;
};


#endif //RENDEROBJECT_HPP
