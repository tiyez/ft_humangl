#ifndef SKELETON_HPP
#define SKELETON_HPP

#include "Node.hpp"
#include "MatrixStack.hpp"
#include <string>

class Skeleton {
public:
	Skeleton(NodeData &&nodedata) {
		_cur_time = 0.f;
		_nodes = std::move (nodedata.nodes);
		_root_index = nodedata.root_index;
		_anim_time = nodedata.animation_time;
		_name = nodedata.name;
	}

	~Skeleton();

	void	Animate(float delta);
	void	SetAnimationTime(float time) { _cur_time = time; }
	void	Draw(MatrixStack &mstack) const;
	void	HighlightNode(int index);
	void	ChangeNodeSize(size_t index, const glm::vec3 &scale_delta);
	void	ChangeNodeColor(size_t index, const glm::vec3 &color_delta);
	void	RotateNodeFrame(size_t node_index, size_t frame_index, glm::vec3 &euler_rot);
	void	PrintNode(size_t index) const;
	void	RecalcAnimationDuration ();

	friend class Console;


private:
	Skeleton() {};
	void UpdateTime(float delta);
	std::vector<TranslateFrame> _translation_frames;
	std::string	_name;
	std::vector<class Node>	_nodes;
	size_t	_root_index;
	size_t	_highlighted_index;
	float	_cur_time;
	float	_anim_time;
	// TODO: add constructor, destructor, copy const, assingn
};

std::ostream &operator<<(std::ostream &o, const glm::vec3 &v);
std::ostream &operator<<(std::ostream &o, const glm::quat &q);
std::ostream &operator<<(std::ostream &o, const Node &node);

#endif //SKELETON_HPP
