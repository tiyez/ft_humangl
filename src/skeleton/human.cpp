#include "Node.hpp"
#include "def.h"
#include "HardNode.hpp"

const struct HardNode	human_skeleton[] = {
	{
		0, -1, { 0, 0, 0, }, { 0, 0, 1, }, 0, { 1.3, 3.14, 0.8, }, { 0, 0, 0, }, { 0, 0, 0, }, 
		{
			{ 0, 0, { 1, 0, 0, }, 0, },
			{ 0, 1, { 1, 0, 0, }, 0.261792, },
			{ 0, 3, { 1, 0, 0, }, 0, },
			{ 1, 0, {0}, 0 },
		},
	},
	{
		0, 0, { 0, 0, 0, }, { 0, 0, 1, }, 0, { 1, 1, 1, }, { 0, -1, 0, }, { 0, 1, 0, }, 
		{
			{ 0, 0, { 1, 0, 0, }, -0.261792, },
			{ 0, 1, { 1, 0, 0, }, 0.261792, },
			{ 0, 3, { 1, 0, 0, }, -0.261792, },
			{ 1, 0, {0}, 0 },
		},
	},
	{
		0, 0, { 0, 0, 0, }, { 0, 0, 1, }, 0, { 0.1, 1.3, 0.2, }, { 1, 1, 0, }, { -1, 1, 0, }, 
		{
			{ 0, 0, { 0, 0, 1, }, 0, },
			{ 0, 1, { 0, 0, 1, }, -0.523583, },
			{ 0, 3, { 0, 0, 1, }, 0, },
			{ 1, 0, {0}, 0 },
		},
	},
	{
		0, 2, { 0, 0, 0, }, { 0, 0, 1, }, 0, { 0.1, 1.3, 0.2, }, { 0, 1, 0, }, { 0, -1, 0, }, 
		{
			{ 0, 0, { 1, 0, 0, }, 0, },
			{ 0, 1, { 1, 0, 0, }, -2.09433, },
			{ 0, 3, { 1, 0, 0, }, 0, },
			{ 1, 0, {0}, 0 },
		},
	},
	{
		0, 0, { 0, 0, 0, }, { 0, 0, 1, }, 0, { 0.1, 1.3, 0.2, }, { -1, 1, 0, }, { 1, 1, 0, }, 
		{
			{ 0, 0, { 0, 0, 1, }, 0, },
			{ 0, 1, { 0, 0, 1, }, 0.523583, },
			{ 0, 3, { 0, 0, 1, }, 0, },
			{ 1, 0, {0}, 0 },
		},
	},
	{
		0, 4, { 0, 0, 0, }, { 0, 0, 1, }, 0, { 0.1, 1.3, 0.2, }, { 0, 1, 0, }, { 0, -1, 0, }, 
		{
			{ 0, 0, { 1, 0, 0, }, 0, },
			{ 0, 1, { 1, 0, 0, }, -2.09433, },
			{ 0, 3, { 1, 0, 0, }, 0, },
			{ 1, 0, {0}, 0 },
		},
	},
	{
		0, 0, { 0, 0, 0, }, { 0, 0, 1, }, 0, { 0.1, 1.3, 0.2, }, { 0, 1, 0, }, { -1, -1, 0, }, 
		{
			{ 0, 0, { 1, 0, 0, }, 0, },
			{ 0, 1, { 1, 0, 0, }, -1.91981, },
			{ 0, 3, { 1, 0, 0, }, 0, },
			{ 1, 0, {0}, 0 },
		},
	},
	{
		0, 6, { 0, 0, 0, }, { 0, 0, 1, }, 0, { 0.1, 1.3, 0.2, }, { 0, 1, 0, }, { 0, -1, 0, }, 
		{
			{ 0, 0, { 1, 0, 0, }, 0, },
			{ 0, 1, { 1, 0, 0, }, 2.79244, },
			{ 0, 3, { 1, 0, 0, }, 0, },
			{ 1, 0, {0}, 0 },
		},
	},
	{
		0, 0, { 0, 0, 0, }, { 0, 0, 1, }, 0, { 0.1, 1.3, 0.2, }, { 0, 1, 0, }, { 1, -1, 0, }, 
		{
			{ 0, 0, { 1, 0, 0, }, 0, },
			{ 0, 1, { 1, 0, 0, }, -1.91981, },
			{ 0, 3, { 1, 0, 0, }, 0, },
			{ 1, 0, {0}, 0 },
		},
	},
	{
		0, 8, { 0, 0, 0, }, { 0, 0, 1, }, 0, { 0.1, 1.3, 0.2, }, { 0, 1, 0, }, { 0, -1, 0, }, 
		{
			{ 0, 0, { 1, 0, 0, }, 0, },
			{ 0, 1, { 1, 0, 0, }, 2.79244, },
			{ 0, 3, { 1, 0, 0, }, 0, },
			{ 1, 0, {0}, 0 },
		},
	},
	{ 1, 0, {0}, {0}, 0, {0}, {0}, {0}, {} },
};

struct NodeData	create_nodes_from_hardnodes (const RenderObject *model, const struct HardNode *hardnode) {
	std::vector<class Node *>	nodes;
	class Node	*root = nullptr;
	struct NodeData	data = { 0, 0, 0 };

	while (!hardnode->_end) {
		std::vector<struct RotationFrame>	frames;
		const struct HardFrame	*hardframe;

		nodes.push_back (new class Node (
			glm::vec3 (hardnode->translation[0], hardnode->translation[1], hardnode->translation[2]),
			glm::angleAxis (hardnode->rotation_angle, glm::vec3 (hardnode->rotation_axis[0], hardnode->rotation_axis[1], hardnode->rotation_axis[2])),
			glm::vec3 (hardnode->scale[0], hardnode->scale[1], hardnode->scale[2]),
			glm::vec3 (hardnode->self_origin[0], hardnode->self_origin[1], hardnode->self_origin[2]),
			glm::vec3 (hardnode->parent_origin[0], hardnode->parent_origin[1], hardnode->parent_origin[2]),
			model
			));
		hardframe = hardnode->frames;
		while (!hardframe->_end) {
			frames.push_back ({ hardframe->time, glm::vec3 (hardframe->axis[0], hardframe->axis[1], hardframe->axis[2]), hardframe->angle });
			data.animation_time = glm::max (data.animation_time, hardframe->time);
			hardframe += 1;
		}
		nodes.back ()->SetRotationFrames (std::move (frames));
		if (hardnode->parent >= 0) {
			nodes.back ()->SetParent (nodes[hardnode->parent]);
		} else if (root) {
			Error ("Skeleton has more than one root");
		} else {
			root = nodes.back ();
		}
		data.nodes_count += 1;
		hardnode += 1;
	}
	if (!root) {
		Error ("Skeleton with no root");
	}
	data.root = root;
	return (data);
}

struct NodeData create_human(const RenderObject *model) {
	return (create_nodes_from_hardnodes (model, human_skeleton));
}