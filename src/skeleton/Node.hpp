#ifndef NODE_HPP
#define NODE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <GLFW/glfw3.h>
#include <vector>

#include "RenderObject.hpp"

struct RotationFrame {
	float		time;
	glm::vec3	axis;
	float		angle;
};

class Node { // TODO: cleanup this mess
public:
	glm::vec3	translation;
	glm::quat	rotation;
	glm::vec3	scale;
	glm::vec3	self_origin;
	glm::vec3	parent_origin;
	const RenderObject *model; // TODO: use smart ptr??
	class Node	*parent;
	std::vector<class Node *>	childs;
	std::vector<RotationFrame>	rot_frames;
	glm::vec3	color;
	bool		selected;

	Node(	glm::vec3 translation,
			glm::quat rotation,
			glm::vec3 scale,
			glm::vec3 self_origin,
			glm::vec3 parent_origin,
			const RenderObject *model) :
				translation(translation),
				rotation(rotation),
				scale(scale),
				self_origin(self_origin),
				parent_origin(parent_origin),
				model(model),
				parent(nullptr),
				color(glm::vec3(0)),
				selected(false){}

	void SetParent (class Node *parent);
	void SetRotationFrames (std::vector<RotationFrame> &&frames);

	// TODO def constructor, destructor, copy constructor, assign operator
};

#endif //NODE_HPP
