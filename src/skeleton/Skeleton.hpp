#ifndef SKELETON_HPP
#define SKELETON_HPP

#include "Node.hpp"

class Skeleton {
public:
	Skeleton(const RenderObject *model) {	// TODO: remove slider
		_cur_time = 0.f;
		_anim_time = 3.f;
		_node_hierarchy = create_human(model);
	}

	~Skeleton();

	void	Animate(float delta);
	void	Draw(const glm::mat4 &vp) const;

private:
	Skeleton() {};
	void UpdateTime(float delta);

	Node	*_node_hierarchy;
	float	_cur_time;
	float	_anim_time;
	// TODO: add constructor, destructor, copy const, assingn
};


#endif //SKELETON_HPP
