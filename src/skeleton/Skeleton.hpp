#ifndef SKELETON_HPP
#define SKELETON_HPP

#include "Node.hpp"

class Skeleton {
public:
	Skeleton(const RenderObject *model, float slider) {
		_cur_time = 0.f;
		_anim_time = 5.f;
		_node_hierarchy = create_human(slider, model);
	}

	~Skeleton();

	void	animate(float delta);
	void	draw(const glm::mat4 &vp) const;

private:
	Skeleton() {};

	Node	*_node_hierarchy;
	float	_cur_time;
	float	_anim_time;
	// TODO: add constructor, destructor, copy const, assingn
};


#endif //SKELETON_HPP
