
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
	void	serialize_node (class Node *node, int parent);

public:
	NodeSerializer (const std::string &name);
	void		serialize_root (class Node *root);
	std::string	finalize ();
};

#endif /* Node_Serializer_Header */
