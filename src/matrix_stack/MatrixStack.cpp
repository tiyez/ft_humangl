#include "MatrixStack.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

glm::mat4	&MatrixStack::push () {
	if (matricies_count <= 0) {
		matricies[matricies_count] = glm::mat4 (1);
	} else {
		matricies[matricies_count] = top ();
	}
	matricies_count += 1;
	return (top ());
}

glm::mat4	&MatrixStack::pop () {
	matricies_count -= 1;
	return (top ());
}

glm::mat4	&MatrixStack::top () {
	return (matricies[matricies_count - 1]);
}

void	MatrixStack::scale (const glm::vec3 &dim) {
	top () *= glm::scale (dim);
}

void	MatrixStack::rotate (float angle, const glm::vec3 &axis) {
	top () *= glm::rotate (angle, axis);
}

void	MatrixStack::rotate(const glm::quat &rot) {
	top () *= glm::mat4_cast(rot);
}

void	MatrixStack::translate (const glm::vec3 &delta) {
	top () *= glm::translate (delta);
}