#ifndef NODE_HPP
#define NODE_HPP

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <vector>

class Node {
public:
	glm::vec3	rotation_axis;
	float		rotation_angle;
	glm::vec3	self_origin;
	glm::vec3	parent_origin;
	glm::vec3	scale;
	class Node	*parent;
	std::vector<class Node *>	childs;

	Node (glm::vec3 rotation_axis,
		  float rotation_angle,
		  glm::vec3 self_origin,
		  glm::vec3 parent_origin,
		  glm::vec3 scale)
		  : rotation_axis(rotation_axis)
		  , rotation_angle(rotation_angle)
		  , self_origin(self_origin)
		  , parent_origin(parent_origin)
		  , scale(scale)
		  , parent(0) {}

	void set_parent (class Node *parent);

	// TODO destructor, copy constructor, assign operator
};

#endif //NODE_HPP
