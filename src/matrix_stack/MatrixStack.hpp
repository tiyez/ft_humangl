#ifndef MATRIXSTACK_HPP
#define MATRIXSTACK_HPP

#include <glm/glm.hpp>

class MatrixStack {
	glm::mat4	matricies[8];
	size_t		matricies_count;

public:
	MatrixStack (): matricies_count (0) {}
	glm::mat4	&push ();
	glm::mat4	&pop ();
	glm::mat4	&top ();
	void		scale (const glm::vec3 &dim);
	void		rotate (float angle, const glm::vec3 &axis);
	void		translate (const glm::vec3 &delta);

	// TODO: add copy constructor, assingnation op, destructor
};

#endif //MATRIXSTACK_HPP
