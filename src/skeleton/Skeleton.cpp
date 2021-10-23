#include "Skeleton.hpp"
#include "MatrixStack.hpp"
#include "def.h"

#include <iostream>

// HIERARCHY
// TODO: move all *_hierarchy to distinct class?? (Note(viktor): no, lets leave all node related operation in one place)


static glm::quat get_cur_rotation(std::vector<RotationFrame> &frames, float cur_time) {

	if (frames.size () == 0) {
		return (glm::angleAxis (0.f, glm::vec3 (1, 0, 0)));
	} else if (frames.size () == 1) {
		return (glm::angleAxis (frames[0].angle, frames[0].axis));
	}

	int		begin_index = -1;
	int		end_index = -1;

	for (size_t index = 0; index < frames.size (); index += 1) {
		if (frames[index].time < cur_time) {
			begin_index = index;
		} else {
			end_index = index;
			break ;
		}
	}

	if (begin_index < 0) {
		return (glm::angleAxis (frames[0].angle, frames[0].axis));
	} else if (end_index < 0) {
		return (glm::angleAxis (frames[begin_index].angle, frames[begin_index].axis));
	}

	RotationFrame	*begin = &frames[begin_index];
	RotationFrame	*end = &frames[end_index];

	float mixed_time = (cur_time - begin->time) / (end->time - begin->time);

	return glm::mix(glm::angleAxis(begin->angle, begin->axis),
					glm::angleAxis(end->angle, end->axis),
					mixed_time);
}





// HIERARCHY END

Skeleton::~Skeleton() {
}

void Skeleton::UpdateTime(float delta) {
	_cur_time += delta;
	if (_cur_time > _anim_time) {
		_cur_time = ((_cur_time / _anim_time) - (ssize_t)(_cur_time / _anim_time)) * _anim_time;
	}
}

static void update_hierarchy(std::vector<class Node> &nodes, size_t index, float cur_time) {
	for (auto child : nodes[index].childs) {
		update_hierarchy(nodes, child, cur_time);
	}
	nodes[index].rotation = get_cur_rotation(nodes[index].rot_frames, cur_time);
}

void Skeleton::Animate(float delta) {
	UpdateTime(delta);
	update_hierarchy(_nodes, _root_index, _cur_time);
}

static void draw_hierarchy(class MatrixStack &stack, const std::vector<class Node> &nodes, size_t index, int highlighted_index) {
	const class Node	*node = &nodes[index];

	stack.push ();
	if (node->parent_index >= 0) {
		stack.translate ((nodes[node->parent_index].scale / 2.f) * node->parent_origin);
	}
	stack.rotate (node->rotation);	// TODO: is it possible always rotate by quat without errors? (Note(viktor): its guaranteed by glm)
	stack.translate (-((node->scale / 2.f) * node->self_origin));
	stack.push ();
	stack.scale (node->scale);
	node->model->RenderColor(stack.top (), node->color, (int) index == highlighted_index);
	stack.pop ();
	for (auto &child : node->childs) {
		draw_hierarchy (stack, nodes, child, highlighted_index);
	}
	stack.pop ();
}

void Skeleton::Draw(MatrixStack &mstack) const {
	if (_highlighted_index < _nodes.size ()) {
		draw_hierarchy(mstack, _nodes, _root_index, _highlighted_index);
	} else {
		draw_hierarchy(mstack, _nodes, _root_index, -1);
	}
}

void Skeleton::ChangeNodeSize(size_t index, const glm::vec3 &scale_delta) {
	if (index < _nodes.size ()) {
		_nodes[index].scale += scale_delta;
	} else {
		Error ("invalid index (index: %zu; nodes count: %zu)", index, _nodes.size ());
	}
}

void Skeleton::PrintNode(size_t index) const {
	if (index < _nodes.size ()) {
		std::cout << _nodes[index] << std::endl;
	} else {
		Error ("invalid index (index: %zu; nodes count: %zu)", index, _nodes.size ());
	}
}

void Skeleton::ChangeNodeColor(size_t index, const glm::vec3 &color_delta) {
	if (index < _nodes.size ()) {
		_nodes[index].color += color_delta;
		_nodes[index].color.x = glm::clamp(_nodes[index].color.x, 0.f, 0.9f);
		_nodes[index].color.y = glm::clamp(_nodes[index].color.y, 0.f, 0.9f);
		_nodes[index].color.z = glm::clamp(_nodes[index].color.z, 0.f, 0.9f);
	} else {
		Error ("invalid index (index: %zu; nodes count: %zu)", index, _nodes.size ());
	}
}

void	Skeleton::HighlightNode(int index) {
	if (index >= 0 && index < (int) _nodes.size ()) {
		_highlighted_index = index;
	} else {
		_highlighted_index = _nodes.size ();
	}
}

void	Skeleton::RotateNodeFrame (size_t node_index, size_t frame_index, float rotate_x, float rotate_y) {
	if (node_index < _nodes.size ()) {
		class Node	*node = &_nodes[node_index];

		if (frame_index < node->rot_frames.size ()) {
			struct RotationFrame	&frame = node->rot_frames[frame_index];
			glm::quat	quat = glm::angleAxis (frame.angle, frame.axis);

			quat *= glm::angleAxis (rotate_x, glm::vec3 (0, 1, 0)) * glm::angleAxis (rotate_y, glm::vec3 (1, 0, 0));
			frame.axis = glm::axis (quat);
			frame.angle = glm::angle (quat);
		} else {
			Error ("invalid frame_index (frame_index: %zu; frames count: %zu)", frame_index, node->rot_frames.size ());
		}
	} else {
		Error ("invalid node_index (node_index: %zu; nodes count: %zu)", node_index, _nodes.size ());
	}
}








std::ostream &operator<<(std::ostream &o, const glm::vec3 &v) {
	o << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return o;
}

std::ostream &operator<<(std::ostream &o, const glm::quat &q) {
	o << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
	return o;
}

std::ostream &operator<<(std::ostream &o, const Node &node) {
	o << "Scale: " << node.scale << std::endl;
	o << "Rotation: " << node.rotation << std::endl;
	o << "Translation: " << node.translation << std::endl;
	return o;
}
