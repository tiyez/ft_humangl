#include "MatrixStack.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "ftm.hpp"

ftm::mat4	&MatrixStack::push () {
	if (matricies_count <= 0) {
		matricies[matricies_count] = ftm::mat4 (1);
	} else {
		matricies[matricies_count] = top ();
	}
	matricies_count += 1;
	return (top ());
}

ftm::mat4	&MatrixStack::pop () {
	matricies_count -= 1;
	return (top ());
}

ftm::mat4	&MatrixStack::top () {
	return (matricies[matricies_count - 1]);
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
