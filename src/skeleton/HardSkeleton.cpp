#include "HardSkeleton.hpp"
#include "def.h"

struct NodeData	create_nodes_from_hardnodes (const RenderObject *model, const struct HardNode *hardnode) {
	struct NodeData	data {};

	data.root_index = -1;
	while (!hardnode->_end) {
		std::vector<struct RotationFrame>	frames;
		const struct HardFrame	*hardframe;

		data.nodes.push_back (Node (
			ftm::vec3 (hardnode->translation[0], hardnode->translation[1], hardnode->translation[2]),
			ftm::angleAxis (hardnode->rotation_angle, ftm::vec3 (hardnode->rotation_axis[0], hardnode->rotation_axis[1], hardnode->rotation_axis[2])),
			ftm::vec3 (hardnode->scale[0], hardnode->scale[1], hardnode->scale[2]),
			ftm::vec3 (hardnode->self_origin[0], hardnode->self_origin[1], hardnode->self_origin[2]),
			ftm::vec3 (hardnode->parent_origin[0], hardnode->parent_origin[1], hardnode->parent_origin[2]),
			model
			));
		hardframe = hardnode->frames;
		while (!hardframe->_end) {
			frames.push_back ({ hardframe->time, ftm::vec3 (hardframe->axis[0], hardframe->axis[1], hardframe->axis[2]), hardframe->angle });
			data.animation_time = ftm::max (data.animation_time, hardframe->time);
			hardframe += 1;
		}
		data.nodes.back ().rot_frames = std::move (frames);
		if (hardnode->parent >= 0) {
			data.nodes.back ().parent_index = hardnode->parent;
			data.nodes[hardnode->parent].childs.push_back (data.nodes.size () - 1);
		} else if (data.root_index >= 0) {
			Error ("Skeleton has more than one root");
		} else {
			data.root_index = data.nodes.size () - 1;
		}
		hardnode += 1;
	}
	if (data.root_index < 0) {
		Error ("Skeleton with no root");
	}
	return (data);
}

struct NodeData	create_nodedata (const RenderObject *model, std::string name) {
	for (size_t index = 0; hardskeletons[index].name; index += 1) {
		if (0 == name.compare (hardskeletons[index].name)) {
			struct NodeData	nodedata = create_nodes_from_hardnodes (model, hardskeletons[index].hardnodes);

			if (hardskeletons[index].hardtranslations) {
				for (size_t i = 0; i < INT64_MAX; ++i) {
					if (hardskeletons[index].hardtranslations[i]._end) {
						break ;
					}
					float const *f = hardskeletons[index].hardtranslations[i].axis;
					ftm::vec3 v = ftm::vec3 (*f, *(f + 1), *(f + 2));
					nodedata.translations.push_back({ hardskeletons[index].hardtranslations[i].time, v });
				}
			}
			nodedata.name = name;
			return (nodedata);
		}
	}
	Error ("hardskeleton '%s' not found", name.c_str ());
	return {};
}



