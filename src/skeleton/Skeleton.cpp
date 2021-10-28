#include "Skeleton.hpp"
#include "MatrixStack.hpp"
#include "def.h"

#include <iostream>
#include "ftm.hpp"

static ftm::quat get_cur_rotation(std::vector<RotationFrame> &frames, float cur_time) {

	if (frames.size () == 0) {
		return (ftm::angleAxis (0.f, ftm::vec3 (1, 0, 0)));
	} else if (frames.size () == 1) {
		return (ftm::angleAxis (frames[0].angle, frames[0].axis));
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
		return (ftm::angleAxis (frames[0].angle, frames[0].axis));
	} else if (end_index < 0) {
		return (ftm::angleAxis (frames[begin_index].angle, frames[begin_index].axis));
	}

	RotationFrame	*begin = &frames[begin_index];
	RotationFrame	*end = &frames[end_index];

	float mixed_time = (cur_time - begin->time) / (end->time - begin->time);

	return ftm::mix(ftm::angleAxis(begin->angle, begin->axis),
					ftm::angleAxis(end->angle, end->axis),
					mixed_time);
}

static ftm::vec3 get_cur_translation(std::vector<TranslationFrame> &frames, float cur_time) {

	if (frames.size () == 0) {
		return (ftm::vec3());
	} else if (frames.size () == 1) {
		return (frames[0].translate);
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
		return (frames[0].translate);
	} else if (end_index < 0) {
		return (frames[begin_index].translate);
	}

	TranslationFrame	*begin = &frames[begin_index];
	TranslationFrame	*end = &frames[end_index];

	float mixed_time = (cur_time - begin->time) / (end->time - begin->time);

	return ftm::mix(begin->translate, end->translate, mixed_time);
}

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
	_cur_translation = get_cur_translation(_translation_frames, _cur_time);
	update_hierarchy(_nodes, _root_index, _cur_time);
}

static void draw_hierarchy(class MatrixStack &stack, const std::vector<class Node> &nodes, size_t index, int highlighted_index) {
	const class Node	*node = &nodes[index];

	stack.push ();
	if (node->parent_index >= 0) {
		stack.translate ((nodes[node->parent_index].scale / 2.f) * node->parent_origin);
	}
	stack.rotate (node->rotation);	// TODO: is it possible always rotate by quat without errors? (Note(viktor): its guaranteed by glm) (Note(Vitalii): but if its our own quat?:D)
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
	mstack.push();

	mstack.translate(_cur_translation);
	if (_highlighted_index < _nodes.size ()) {
		draw_hierarchy(mstack, _nodes, _root_index, _highlighted_index);
	} else {
		draw_hierarchy(mstack, _nodes, _root_index, -1);
	}
	mstack.pop();
}

void Skeleton::ChangeNodeSize(size_t index, const ftm::vec3 &scale_delta) {
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

void Skeleton::ChangeNodeColor(size_t index, const ftm::vec3 &color_delta) {
	if (index < _nodes.size ()) {
		_nodes[index].color += color_delta;
		_nodes[index].color.x = ftm::clamp(_nodes[index].color.x, 0.f, 0.9f);
		_nodes[index].color.y = ftm::clamp(_nodes[index].color.y, 0.f, 0.9f);
		_nodes[index].color.z = ftm::clamp(_nodes[index].color.z, 0.f, 0.9f);
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

void	Skeleton::RotateNodeFrame (size_t node_index, size_t frame_index, ftm::vec3 &euler_rot) {
	if (node_index < _nodes.size ()) {
		class Node	*node = &_nodes[node_index];

		if (frame_index < node->rot_frames.size ()) {
			struct RotationFrame	&frame = node->rot_frames[frame_index];
			ftm::quat	quat = ftm::angleAxis (frame.angle, frame.axis);

			quat *= ftm::angleAxis (euler_rot.x, ftm::vec3 (0, 1, 0)) * ftm::angleAxis (euler_rot.y, ftm::vec3 (1, 0, 0)) * ftm::angleAxis(euler_rot.z, ftm::vec3 (0, 0, 1));
			frame.axis = ftm::axis (quat);
			frame.angle = ftm::angle (quat);
		} else {
			Error ("invalid frame_index (frame_index: %zu; frames count: %zu)", frame_index, node->rot_frames.size ());
		}
	} else {
		Error ("invalid node_index (node_index: %zu; nodes count: %zu)", node_index, _nodes.size ());
	}
}

void Skeleton::TranslateFrame(size_t frame_index, ftm::vec3 &translation) {
	if (frame_index < _translation_frames.size()) {
		_translation_frames[frame_index].translate += translation;
	}
	else {
		Error ("invalid frame_index (frame_index: %zu; nodes count: %zu)", frame_index, _translation_frames.size ());
	}
}

void	Skeleton::RecalcAnimationDuration () {
	_anim_time = 0;
	for (auto &node : _nodes) {
		for (auto &frame : node.rot_frames) {
			_anim_time = ftm::max (_anim_time, frame.time);
		}
	}
	for (auto &trans : _translation_frames) {
		_anim_time = ftm::max (_anim_time, trans.time);
	}
}

/* Output glm types */
/*

std::ostream &operator<<(std::ostream &o, const glm::vec4 &v) {
	o << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return o;
}

std::ostream &operator<<(std::ostream &o, const glm::vec3 &v) {
	o << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return o;
}

std::ostream &operator<<(std::ostream &o, const glm::mat4 &mat) {
	float const *matptr = glm::value_ptr(mat);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j ) {
			o << matptr[4 * i + j] << " ";
		}
		o << std::endl;
	}
	return o;
}

std::ostream &operator<<(std::ostream &o, const glm::quat &q) {
	o << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
	return o;
}
*/

std::ostream &operator<<(std::ostream &o, const ftm::vec3 &v) {
	o << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return o;
}

std::ostream &operator<<(std::ostream &o, const ftm::mat4 &mat) {
	float const *matptr = (float*)&mat;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j ) {
			o << matptr[4 * i + j] << " ";
		}
		o << std::endl;
	}
	return o;
}

std::ostream &operator<<(std::ostream &o, const ftm::quat &q) {
	o << "(" << q.i << ", " << q.j << ", " << q.k << ", " << q.w << ")";
	return o;
}

std::ostream &operator<<(std::ostream &o, const Node &node) {
	o << "Scale: " << node.scale << std::endl;
	o << "Rotation: " << node.rotation << std::endl;
	o << "Translation: " << node.translation << std::endl;
	return o;
}
