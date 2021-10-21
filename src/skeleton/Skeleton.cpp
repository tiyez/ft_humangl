#include "Skeleton.hpp"
#include "MatrixStack.hpp"
#include "def.h"

// HIERARCHY

static void draw_hierarchy(class MatrixStack &stack, const class Node &node, const glm::mat4 &vp) {	// TODO: move to Node.cpp??
	stack.push ();
	if (node.parent) {
		stack.translate ((node.parent->scale / 2.f) * node.parent_origin);
	}
	stack.rotate (node.rotation);	// TODO: is it possible always rotate by quat without errors?
	stack.translate (-((node.scale / 2.f) * node.self_origin));
	stack.push ();
	stack.scale (node.scale);
	node.model->RenderColor(vp * stack.top (), node.color, static_cast<GLint>(node.selected));
	stack.pop ();
	for (auto &child : node.childs) {
		draw_hierarchy (stack, *child, vp);
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

void Skeleton::Draw(const glm::mat4 &vp) const {
	MatrixStack stack;
	draw_hierarchy(stack, *_node_hierarchy, vp);
}
