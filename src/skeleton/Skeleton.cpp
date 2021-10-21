#include "Skeleton.hpp"
#include "MatrixStack.hpp"
#include "def.h"

// HIERARCHY TODO: move all *_hierarchy to distinct class??

static void draw_hierarchy(class MatrixStack &stack, const class Node &node) {	// TODO: move to Node.cpp??
	stack.push ();
	if (node.parent) {
		stack.translate ((node.parent->scale / 2.f) * node.parent_origin);
	}
	stack.rotate (node.rotation);	// TODO: is it possible always rotate by quat without errors?
	stack.translate (-((node.scale / 2.f) * node.self_origin));
	stack.push ();
	stack.scale (node.scale);
	node.model->RenderColor(stack.top (), node.color, static_cast<GLint>(node.selected));
	stack.pop ();
	for (auto &child : node.childs) {
		draw_hierarchy (stack, *child);
	}
	stack.pop ();
}

static void delete_hierarchy(Node *node) {	// TODO: change signature to reference instead pointer??
	if (!node->childs.empty()) {
		for (auto child : node->childs) {
			delete_hierarchy(child);
		}
	}
	delete node;
}

static glm::quat get_cur_rotation(std::vector<RotationFrame> &rot_frames, float cur_time) {
	if (rot_frames.empty()) {
		Error("Rotation frames is absent");
		return {};
	}

	RotationFrame	*frame_begin = &rot_frames[0];
	RotationFrame	*frame_end = &rot_frames[0];

	for (auto &frame : rot_frames) {
		if (frame.time > cur_time) {
			frame_end = &frame;
			break;
		}
		else {
			frame_begin = &frame;
		}
	}

	float mixed_time = (frame_end->time - cur_time) / (frame_end->time - frame_begin->time);

	return glm::mix(glm::angleAxis(frame_begin->angle, frame_begin->axis),
					glm::angleAxis(frame_end->angle, frame_end->axis),
					mixed_time);
}


static void update_hierarchy(Node *node, float cur_time) {
	if (!node->childs.empty()) {
		for (auto child : node->childs) {
			update_hierarchy(child, cur_time);
		}
	}
	node->rotation = get_cur_rotation(node->rot_frames, cur_time);
}

static void select_node_hierarchy(Node *node, int *node_number) {
	if (*node_number == 0) {
		node->selected = true;
	}
	else {
		node->selected = false;
	}
	*node_number -= 1;
	if (!node->childs.empty()) {
		for (auto child : node->childs) {
			select_node_hierarchy(child, node_number);
		}
	}
}

static void change_scale_selected_hierarchy(Node *node, glm::vec3 &scale_delta) {
	if (!node->childs.empty()) {
		for (auto child : node->childs) {
			change_scale_selected_hierarchy(child, scale_delta);
		}
	}
	if (node->selected) {
		node->scale += scale_delta;
	}
}

// HIERARCHY END

Skeleton::~Skeleton() {
	delete_hierarchy(_node_hierarchy);
}

void Skeleton::UpdateTime(float delta) {
	_cur_time += delta;
	if (_cur_time > _anim_time) {
		_cur_time = ((_cur_time / _anim_time) - (ssize_t)(_cur_time / _anim_time)) * _anim_time;
	}
}

void Skeleton::Animate(float delta) {
	UpdateTime(delta);
	update_hierarchy(_node_hierarchy, _cur_time);
}

void Skeleton::Draw(MatrixStack &mstack) const {
	draw_hierarchy(mstack, *_node_hierarchy);
}

void Skeleton::SelectNode(int node_num) const {
	node_num = abs(node_num) + _nodes_count;
	node_num = node_num % (_nodes_count + 1);
	select_node_hierarchy(_node_hierarchy, &node_num);
}

void Skeleton::ChangeSizeSelected(glm::vec3 &scale_delta) const {
	change_scale_selected_hierarchy(_node_hierarchy, scale_delta);
}
