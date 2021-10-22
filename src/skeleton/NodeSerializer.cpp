
#include "NodeSerializer.hpp"

NodeSerializer::NodeSerializer (const std::string &name): node_counter (0) {
	stream << "const struct HardNode\tskeleton_" << name << "[] = {" << std::endl;
}

void	NodeSerializer::serialize_glmvec3 (const glm::vec3 &vector) {
	stream << "{ " << vector.x << ", " << vector.y << ", " << vector.z << ", }, ";
}

void	NodeSerializer::serialize_node (class Node *node, int parent) {
	stream << "\t{" << std::endl;
	stream << "\t\t0, " << parent << ", ";
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
	parent = node_counter;
	node_counter += 1;
	for (auto &child : node->childs) {
		serialize_node (child, parent);
	}
}

void	NodeSerializer::serialize_root (class Node *root) {
	serialize_node (root, -1);
}

std::string	NodeSerializer::finalize () {
	stream << "\t{ 1, 0, {0}, {0}, 0, {0}, {0}, {0}, {} }," << std::endl << "};" << std::endl;
	return (stream.str ());
}

