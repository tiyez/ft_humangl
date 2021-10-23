
#ifndef Console_Header
#define Console_Header

#include "Skeleton.hpp"

class Console {
	Skeleton	skeleton;
	int			_frame_index;
	int			_node_index;

public:
	Console (Skeleton &&skeleton): skeleton (skeleton), _frame_index (-1), _node_index (-1) {}
	void	listen_command ();
	void	update (struct Input &input, float delta);

	Skeleton	&get_skeleton () { return skeleton; }
};







#endif /* Console_Header */
