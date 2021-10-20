#include "Node.hpp"
#include "MatrixStack.hpp"

void draw_hierarchy(class MatrixStack &stack, const class Node &node, const glm::mat4 &vp) {
	stack.push ();
	if (node.parent) {
		stack.translate ((node.parent->scale / 2.f) * node.parent_origin);
	}
	stack.rotate (node.rotation);	// TODO: is it possible always rotate by quat without errors?
	stack.translate (-((node.scale / 2.f) * node.self_origin));
	stack.push ();
	stack.scale (node.scale);
	node.model->Render(vp * stack.top ());
	stack.pop ();
	for (auto &child : node.childs) {
		draw_hierarchy (stack, *child, vp);
	}
	stack.pop ();
}

void delete_hierarchy(Node *node) {
	if (!node->childs.empty()) {
		for (auto child : node->childs) {
			delete_hierarchy(child);
		}
	}
	delete node;
}
