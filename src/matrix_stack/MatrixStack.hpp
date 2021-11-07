#ifndef MATRIXSTACK_HPP
#define MATRIXSTACK_HPP

#include "ftm.hpp"
#include <vector>

class MatrixStack {
	std::vector<ftm::mat4>	matricies;

public:
	MatrixStack () {}
	ftm::mat4	&push ();
	void		pop ();
	ftm::mat4	&top ();
	void		scale (const ftm::vec3 &dim);
	void		rotate (float angle, const ftm::vec3 &axis);
	void		rotate (const ftm::quat &rot);
	void		translate (const ftm::vec3 &delta);
	void		transform (const ftm::mat4 &mat);

	// TODO: add copy constructor, assingnation op, destructor
};

#endif //MATRIXSTACK_HPP
