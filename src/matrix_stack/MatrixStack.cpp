#include "MatrixStack.hpp"

#include "ftm.hpp"

ftm::mat4	&MatrixStack::push () {
	if (matricies.size () <= 0) {
		matricies.push_back (ftm::mat4 (1));
	} else {
		matricies.push_back (top ());
	}
	return (top ());
}

void	MatrixStack::pop () {
	if (matricies.size () > 0) {
		matricies.pop_back ();
	}
}

ftm::mat4	&MatrixStack::top () {
	return (matricies.back ());
}

void	MatrixStack::scale (const ftm::vec3 &dim) {
	top () *= ftm::scale (dim);
}

void	MatrixStack::rotate (float angle, const ftm::vec3 &axis) {
	top () *= ftm::rotate (angle, axis);
}

void	MatrixStack::rotate(const ftm::quat &rot) {
	top () *= ftm::mat4_cast(rot);
}

void	MatrixStack::translate (const ftm::vec3 &delta) {
	top () *= ftm::translate (delta);
}

void MatrixStack::transform(const ftm::mat4 &mat) {
	top () *= mat;
}
