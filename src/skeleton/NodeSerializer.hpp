
#ifndef Node_Serializer_Header
#define Node_Serializer_Header

#include <sstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Node.hpp"

class NodeSerializer {
	std::stringstream	stream;
	int					node_counter;
	std::vector<std::string>	names;

	void	serialize_glmvec3 (const glm::vec3 &vector);

public:
	NodeSerializer ();
	void		serialize_translations (const std::vector<TranslateFrame> &translatinos, const std::string &name);
	void		serialize_nodes (const std::vector<class Node> &nodes, const std::string &name);
	void		serialize_nodedata (const struct NodeData &nodedata);
	std::string	finalize ();
};

#endif /* Node_Serializer_Header */
