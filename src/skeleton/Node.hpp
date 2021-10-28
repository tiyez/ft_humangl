#ifndef NODE_HPP
#define NODE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include "ftm.hpp"

#include "RenderObject.hpp"

struct RotationFrame {
	float		time;
	ftm::vec3	axis;
	float		angle;
};

struct TranslationFrame {
	float time;
	ftm::vec3 translate;
};

struct NodeData {
	float		animation_time;
	size_t		nodes_count;
	std::vector<TranslationFrame> translations;
	std::vector<class Node>	nodes;
	int			root_index;
	std::string	name;
};

// Note(viktor): seems like it should be struct. It doesn't have behaviour, only data.
class Node { // TODO: cleanup this mess
public:
	ftm::vec3	translation;
	ftm::quat	rotation;
	ftm::vec3	scale;
	ftm::vec3	self_origin;
	ftm::vec3	parent_origin;
	const RenderObject *model; // TODO: use smart ptr??
	int			parent_index;
	std::vector<size_t>	childs;
	std::vector<RotationFrame>	rot_frames;
	ftm::vec3	color;

	Node(	ftm::vec3 translation,
			ftm::quat rotation,
			ftm::vec3 scale,
			ftm::vec3 self_origin,
			ftm::vec3 parent_origin,
			const RenderObject *model)
				: translation(translation)
				, rotation(rotation)
				, scale(scale)
				, self_origin(self_origin)
				, parent_origin(parent_origin)
				, model(model)
				, parent_index(-1)
				, color(ftm::vec3(0))
	{ }
	Node (const RenderObject *model)
		: translation(ftm::vec3 (0))
		, rotation(ftm::angleAxis (0.f, ftm::vec3 (1, 0, 0)))
		, scale(ftm::vec3 (1))
		, self_origin(ftm::vec3 (0))
		, parent_origin(ftm::vec3 (0))
		, model(model)
		, parent_index(-1)
		, color(ftm::vec3(0))
	{ }

	// TODO def constructor, destructor, copy constructor, assign operator
};


#endif //NODE_HPP
