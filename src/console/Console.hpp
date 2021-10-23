
#ifndef Console_Header
#define Console_Header

#include "Skeleton.hpp"
#include "HardSkeleton.hpp"

class Console {
	Skeleton	skeleton;
	int			_frame_index;
	int			_node_index;
	const RenderObject *model;

public:
	Console (const RenderObject *model): skeleton (create_nodedata (model, "human")), _frame_index (-1), _node_index (-1), model (model) {}
	bool	listen_command ();
	void	update (struct Input &input, float delta);

	Skeleton	&get_skeleton () { return skeleton; }
};







#endif /* Console_Header */
