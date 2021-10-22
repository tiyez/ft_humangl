
#ifndef Hard_Node_Header
#define Hard_Node_Header

struct HardFrame {
	int		_end;
	float	time;
	float	axis[3];
	float	angle;
};

struct HardNode {
	int					_end;
	int					parent;
	float				translation[3];
	float				rotation_axis[3];
	float				rotation_angle;
	float				scale[3];
	float				self_origin[3];
	float				parent_origin[3];
	struct HardFrame	frames[32];
};

#endif /* Hard_Node_Header */
