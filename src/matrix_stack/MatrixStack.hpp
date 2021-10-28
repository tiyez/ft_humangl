#ifndef MATRIXSTACK_HPP
#define MATRIXSTACK_HPP

#include <glm/glm.hpp>
#include "ftm.hpp"

class MatrixStack {
	ftm::mat4	matricies[8];		// TODO: static on evaluation, really? )
	size_t		matricies_count;

public:
	MatrixStack (): matricies_count (0) {}
	ftm::mat4	&push ();
	ftm::mat4	&pop ();
	ftm::mat4	&top ();
	void		scale (const ftm::vec3 &dim);
	void		rotate (float angle, const ftm::vec3 &axis);
	void		rotate (const ftm::quat &rot);
	void		translate (const ftm::vec3 &delta);
	void		transform (const ftm::mat4 &mat);

	// TODO: add copy constructor, assingnation op, destructor
};

#endif //MATRIXSTACK_HPP
