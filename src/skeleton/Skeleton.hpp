#ifndef SKELETON_HPP
#define SKELETON_HPP

#include "Node.hpp"
#include "MatrixStack.hpp"

class Skeleton {
public:
	Skeleton(const RenderObject *model) {	// TODO: remove slider
		NodeData	data;

		_cur_time = 0.f;
		data = create_human(model);
		_anim_time = data.animation_time;
		_nodes_count = data.nodes_count;
		_node_hierarchy = data.root;
	}

	~Skeleton();

	void	Animate(float delta);
	void	Draw(MatrixStack &mstack) const;
	void	SelectNode(int node_num) const;
	void	ChangeSizeSelected(glm::vec3 &scale_delta) const;
	void	ChangeColorSelected(glm::vec3 &color_delta) const;
	void	PrintSelectedNode() const;

private:
	Skeleton() {};
	void UpdateTime(float delta);

	Node	*_node_hierarchy;
	float	_cur_time;
	float	_anim_time;
	int		_nodes_count;
	// TODO: add constructor, destructor, copy const, assingn
};


#endif //SKELETON_HPP
