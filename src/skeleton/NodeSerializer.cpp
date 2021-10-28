#include "NodeSerializer.hpp"

NodeSerializer::NodeSerializer (): node_counter (0) {
	stream << std::endl << "#include \"HardSkeleton.hpp\"" << std::endl << std::endl;
}

void	NodeSerializer::serialize_ftmvec3 (const ftm::vec3 &vector) {
	stream << "{ " << vector.x << ", " << vector.y << ", " << vector.z << ", }, ";
}

void	NodeSerializer::serialize_translations (const std::vector<TranslationFrame> &translatinos, const std::string &name) {
	stream << "const struct HardTranslationFrame\tskeleton_translations_" << name << "[] = {" << std::endl;

	for (size_t index = 0; index < translatinos.size(); ++index ) {
		stream << "\t{ 0, " << translatinos[index].time << ", ";
		serialize_ftmvec3(translatinos[index].translate);
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
		serialize_ftmvec3(node->translation);
		serialize_ftmvec3(ftm::axis(node->rotation));
		stream << ftm::angle (node->rotation) << ", ";
		serialize_ftmvec3(node->scale);
		serialize_ftmvec3(node->self_origin);
		serialize_ftmvec3(node->parent_origin);
		stream << std::endl << "\t\t{" << std::endl;
		for (auto &rot : node->rot_frames) {
			stream << "\t\t\t{ 0, " << rot.time << ", ";
			serialize_ftmvec3(rot.axis);
			stream << rot.angle << ", }," << std::endl;
		}
		stream << "\t\t\t{ 1, 0, {0}, 0 }," << std::endl << "\t\t}," << std::endl;
		stream << "\t}," << std::endl;
	}
	stream << "\t{ 1, 0, {0}, {0}, 0, {0}, {0}, {0}, {} }," << std::endl << "};" << std::endl;
}

void	NodeSerializer::serialize_nodedata (const struct NodeData &nodedata) {
	serialize_nodes (nodedata.nodes, nodedata.name);
	serialize_translations(nodedata.translations, nodedata.name);
}

std::string	NodeSerializer::finalize () {
	stream << "const struct HardSkeleton	hardskeletons[] = {" << std::endl;
	for (auto &name : names) {
		stream << "\t{ \"" << name << "\", skeleton_" << name << ", skeleton_translations_" << name << "}," << std::endl;
	}
	stream << "\t{ 0, 0, 0}," << std::endl << "};" << std::endl;
	return (stream.str ());
}

