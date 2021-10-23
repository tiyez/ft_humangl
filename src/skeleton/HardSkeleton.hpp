
#ifndef Skeletons_Header
#define Skeletons_Header

#include <string>

#include "HardNode.hpp"
#include "Node.hpp"
#include "RenderObject.hpp"

struct HardSkeleton {
	const char				*name;
	const struct HardNode	*hardnodes;
};

extern const struct HardSkeleton	hardskeletons[];

struct NodeData	create_nodedata (const RenderObject *model, std::string name);

#endif /* Skeletons_Header */
