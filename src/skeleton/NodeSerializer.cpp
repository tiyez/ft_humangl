
#include "NodeSerializer.hpp"

NodeSerializer::NodeSerializer (): node_counter (0) {
	stream << std::endl << "#include \"HardSkeleton.hpp\"" << std::endl << std::endl;
}

void	NodeSerializer::serialize_glmvec3 (const glm::vec3 &vector) {
	stream << "{ " << vector.x << ", " << vector.y << ", " << vector.z << ", }, ";
}

void	NodeSerializer::serialize_translations (const std::vector<TranslateFrame> &translatinos, const std::string &name) {
	stream << "const struct HardNode\tskeleton_translations" << name << "[] = {" << std::endl;

	for (size_t index = 0; index < translatinos.size(); ++index ) {
		stream << "\t{ 0, " << translatinos[index].time << ", ";
		serialize_glmvec3(translatinos[index].translate);
		stream << "},";
	}
	stream << "\t{1, 0, {0, 0, 0}}" << std::endl << "};" << std::endl;
}

void	NodeSerializer::serialize_nodes (const std::vector<class Node> &nodes, const std::string &name) {
	stream << "const struct HardNode\tskeleton_" << name << "[] = {" << std::endl;
	names.push_back (name);

	for (size_t index = 0; index < nodes.size (); index += 1) {
		const class Node	*node = &nodes[index];

		stream << "\t{" << std::endl;
		stream << "\t\t0, " << node->parent_index << ", ";
		serialize_glmvec3 (node->translation);
		serialize_glmvec3 (glm::axis (node->rotation));
		stream << glm::angle (node->rotation) << ", ";
		serialize_glmvec3 (node->scale);
		serialize_glmvec3 (node->self_origin);
		serialize_glmvec3 (node->parent_origin);
		stream << std::endl << "\t\t{" << std::endl;
		for (auto &rot : node->rot_frames) {
			stream << "\t\t\t{ 0, " << rot.time << ", ";
			serialize_glmvec3 (rot.axis);
			stream << rot.angle << ", }," << std::endl;
		}
		stream << "\t\t\t{ 1, 0, {0}, 0 }," << std::endl << "\t\t}," << std::endl;
		stream << "\t}," << std::endl;
	}
	stream << "\t{ 1, 0, {0}, {0}, 0, {0}, {0}, {0}, {} }," << std::endl << "};" << std::endl;
}

void	NodeSerializer::serialize_nodedata (const struct NodeData &nodedata) {
	serialize_nodes (nodedata.nodes, nodedata.name);
}

std::string	NodeSerializer::finalize () {
	stream << "const struct HardSkeleton	hardskeletons[] = {" << std::endl;
	for (auto &name : names) {
		stream << "\t{ \"" << name << "\", skeleton_" << name << ", skeleton_translations_" << name << "}," << std::endl;
	}
	stream << "\t{ 0, 0, }," << std::endl << "};" << std::endl;
	return (stream.str ());
}

