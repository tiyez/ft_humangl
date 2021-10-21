#include "Node.hpp"
#include "def.h"

struct HardFrame {
	int		_end;
	float	time;
	float	axis[3];
	float	angle;
};

struct HardNode {
	int					_end;
	int					parent;
	float				translation[3];
	float				rotation_axis[3];
	float				rotation_angle;
	float				scale[3];
	float				self_origin[3];
	float				parent_origin[3];
	struct HardFrame	frames[32];
};

#define RADIANS(x) ((x) * (3.1415f / 180.f))

const struct HardNode	human_skeleton[] = {
	{ /* torso 0 */
		0, -1, { 0 }, { 1 }, 0, { 1.3f, 3.14f, 0.8f }, { 0 }, { 0 },
		{
			{ 0, 0.0f, { 0, 1, 0 }, RADIANS (-15.f) },
			{ 0, 0.5f, { 0, 1, 0 }, RADIANS (15.f) },
			{ 0, 3.0f, { 0, 1, 0 }, RADIANS (-15.f) },
			{ 1, 0, {0}, 0 },
		},
	},
	{ /* head 1 */
		0, 0, { 0 }, { 1 }, 0, { 1, 1, 1 }, { 0, -1, 0 }, { 0, 1, 0 },
		{
			{ 0, 0.0f, { 1, 0, 0 }, RADIANS (-15.f) },
			{ 0, 1.0f, { 1, 0, 0 }, RADIANS (15.f) },
			{ 0, 3.0f, { 1, 0, 0 }, RADIANS (-15.f) },
			{ 1, 0, {0}, 0 },
		},
	},
	{ /* left_hand 2 */
		0, 0, { 0 }, { 1 }, 0, { 0.1f, 1.3f, 0.2f }, { 1, 1, 0 }, { -1, 1, 0 },
		{
			{ 0, 0.0f, { 0, 0, 1 }, RADIANS (0.f) },
			{ 0, 1.0f, { 0, 0, 1 }, RADIANS (-30.f) },
			{ 0, 3.0f, { 0, 0, 1 }, RADIANS (0.f) },
			{ 1, 0, {0}, 0 },
		},
	},
	{ /* left_lower_hand 3 */
		0, 2, { 0 }, { 1 }, 0, { 0.1f, 1.3f, 0.2f }, { 0, 1, 0 }, { 0, -1, 0 },
		{
			{ 0, 0.0f, { 1, 0, 0 }, RADIANS (0.f) },
			{ 0, 1.0f, { 1, 0, 0 }, RADIANS (-120.f) },
			{ 0, 3.0f, { 1, 0, 0 }, RADIANS (0.f) },
			{ 1, 0, {0}, 0 },
		},
	},
	{ /* right_hand 4 */
		0, 0, { 0 }, { 1 }, 0, { 0.1f, 1.3f, 0.2f }, { -1, 1, 0 }, { 1, 1, 0 },
		{
			{ 0, 0.0f, { 0, 0, 1 }, RADIANS (0.f) },
			{ 0, 1.0f, { 0, 0, 1 }, RADIANS (30.f) },
			{ 0, 3.0f, { 0, 0, 1 }, RADIANS (0.f) },
			{ 1, 0, {0}, 0 },
		},
	},
	{ /* right_lower_hand 5 */
		0, 4, { 0 }, { 1 }, 0, { 0.1f, 1.3f, 0.2f }, { 0, 1, 0 }, { 0, -1, 0 },
		{
			{ 0, 0.0f, { 1, 0, 0 }, RADIANS (0.0f) },
			{ 0, 1.0f, { 1, 0, 0 }, RADIANS (-120.0f) },
			{ 0, 3.0f, { 1, 0, 0 }, RADIANS (0.0f) },
			{ 1, 0, {0}, 0 },
		},
	},
	{ /* left_leg 6 */
		0, 0, { 0 }, { 1 }, 0, { 0.1f, 1.3f, 0.2f }, { 0, 1, 0 }, { -1, -1, 0 },
		{
			{ 0, 0.0f, { 1, 0, 0 }, RADIANS (0.f) },
			{ 0, 1.0f, { 1, 0, 0 }, RADIANS (-110.f) },
			{ 0, 3.0f, { 1, 0, 0 }, RADIANS (0.f) },
			{ 1, 0, {0}, 0 },
		},
	},
	{ /* right_leg 7 */
		0, 0, { 0 }, { 1 }, 0, { 0.1f, 1.3f, 0.2f }, { 0, 1, 0 }, { 1, -1, 0 },
		{
			{ 0, 0.0f, { 1, 0, 0 }, RADIANS (0.f) },
			{ 0, 1.0f, { 1, 0, 0 }, RADIANS (-110.f) },
			{ 0, 3.0f, { 1, 0, 0 }, RADIANS (0.f) },
			{ 1, 0, {0}, 0 },
		},
	},
	{ /* lower_left_leg 8 */
		0, 6, { 0 }, { 1 }, 0, { 0.1f, 1.3f, 0.2f }, { 0, 1, 0 }, { 0, -1, 0 },
		{
			{ 0, 0.0f, { 1, 0, 0 }, RADIANS (0.f) },
			{ 0, 1.0f, { 1, 0, 0 }, RADIANS (160.f) },
			{ 0, 3.0f, { 1, 0, 0 }, RADIANS (0.f) },
			{ 1, 0, {0}, 0 },
		},
	},
	{ /* lower_right_leg 9 */
		0, 7, { 0 }, { 1 }, 0, { 0.1f, 1.3f, 0.2f }, { 0, 1, 0 }, { 0, -1, 0 },
		{
			{ 0, 0.0f, { 1, 0, 0 }, RADIANS (0.f) },
			{ 0, 1.0f, { 1, 0, 0 }, RADIANS (160.f) },
			{ 0, 3.0f, { 1, 0, 0 }, RADIANS (0.f) },
			{ 1, 0, {0}, 0 },
		},
	},
	{ 1, 0, {0}, {0}, 0, {0}, {0}, {0}, {} },
};

#undef RADIANS

Node	*create_nodes_from_hardnodes (const RenderObject *model, const struct HardNode *hardnode) {
	std::vector<class Node *>	nodes;
	class Node	*root = 0;

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
		hardnode += 1;
	}
	if (!root) {
		Error ("Skeleton with no root");
	}
	return (root);
}

Node *create_human(const RenderObject *model) {
	return (create_nodes_from_hardnodes (model, human_skeleton));
}