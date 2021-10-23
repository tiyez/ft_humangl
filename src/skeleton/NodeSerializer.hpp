
#ifndef Node_Serializer_Header
#define Node_Serializer_Header

#include <sstream>
#include <string>
#include <glm/glm.hpp>

#include "Node.hpp"

class NodeSerializer {
	std::stringstream	stream;
	int					node_counter;

	void	serialize_glmvec3 (const glm::vec3 &vector);
	void	serialize_node (const std::vector<class Node> &nodes, size_t index, int parent);

public:
	NodeSerializer (const std::string &name);
	void		serialize_root (const std::vector<class Node> &nodes, size_t root_index);
	void		serialize_nodedata (const struct NodeData &nodedata);
	std::string	finalize ();
};

#endif /* Node_Serializer_Header */
