#include "Node.hpp"
#include "MatrixStack.hpp"

void draw_hierarchy(class MatrixStack &stack, const class Node &node, const glm::mat4 &vp) {
	stack.push ();
	if (node.parent) {
		stack.translate ((node.parent->scale / 2.f) * node.parent_origin);
	}
	if (node.rotation_angle != 0) { // TODO(viktor): epsilon
		stack.rotate (node.rotation_angle, node.rotation_axis);
	}
	stack.translate (-((node.scale / 2.f) * node.self_origin));
	stack.push ();
	stack.scale (node.scale);
	node.model->Render(vp * stack.top ());
	stack.pop ();
	for (auto &child : node.childs) {
		draw_hierarchy (stack, *child, vp);
	}
	stack.pop ();
};

Node *create_human(float slider, RenderObject *model) {
	class Node	*torso = new Node (
			glm::vec3 (0, 1, 0), /* rotation_axis */
			glm::radians(15.f * (slider * 2 - 1)), /* rotation_angle */
			glm::vec3 (0), /* self_origin */
			glm::vec3 (0), /* parent_origin */
			glm::vec3 (1.3f, 3.14f, 0.8f), /* scale */
			model); /* model */

	class Node	*head = new Node (
			glm::vec3 (1, 0, 0), /* rotation_axis */
			glm::radians (15.f * (slider * 2 - 1)), /* rotation_angle */
			glm::vec3 (0, -1, 0), /* self_origin */
			glm::vec3 (0, 1, 0), /* parent_origin */
			glm::vec3 (1),  /* scale */
			model); /* model */
	head->set_parent (torso);

	// hands
	class Node	*left_hand = new Node (
			glm::vec3 (0, 0, 1), /* rotation_axis */
			glm::radians (-30.f + 15.f * (slider * 2 - 1)), /* rotation_angle */
			glm::vec3 (1, 1, 0), /* self_origin */
			glm::vec3 (-1, 1, 0), /* parent_origin */
			glm::vec3 (0.2f, 1.3f, 0.2f), /* scale */
			model);  /* model */
	left_hand->set_parent (torso);
	class Node	*lower_left_hand = new Node (
			glm::vec3 (1, 0, 0), /* rotation_axis */
			glm::radians (-40.f + 30.f * (slider * 2 - 1)), /* rotation_angle */
			glm::vec3 (0, 1, 1), /* self_origin */
			glm::vec3 (0, -1, 1), /* parent_origin */
			glm::vec3 (0.2f, 1.3f, 0.2f), /* scale */
			model);  /* model */
	lower_left_hand->set_parent (left_hand);

	class Node	*right_hand = new Node (
			glm::vec3 (0, 0, 1), /* rotation_axis */
			glm::radians (30.f + 15.f * (slider * -2 + 1)), /* rotation_angle */
			glm::vec3 (-1, 1, 0), /* self_origin */
			glm::vec3 (1, 1, 0), /* parent_origin */
			glm::vec3 (0.2f, 1.3f, 0.2f), /* scale */
			model); /* model */
	right_hand->set_parent (torso);
	class Node	*lower_right_hand = new Node (
			glm::vec3 (1, 0, 0), /* rotation_axis */
			glm::radians (-40.f + 30.f * (slider * 2 - 1)), /* rotation_angle */
			glm::vec3 (0, 1, 1), /* self_origin */
			glm::vec3 (0, -1, 1), /* parent_origin */
			glm::vec3 (0.2f, 1.3f, 0.2f), /* scale */
			model); /* model */
	lower_right_hand->set_parent (right_hand);

	// legs
	class Node	*left_leg = new Node (
			glm::vec3 (0, 0, 1), /* rotation_axis */
			glm::radians (-30.f + 15.f * (slider * 2 - 1)), /* rotation_angle */
			glm::vec3 (1, 1, 0), /* self_origin */
			glm::vec3 (-1, -1, 0), /* parent_origin */
			glm::vec3 (0.2f, 1.3f, 0.2f), /* scale */
			model); /* model */
	left_leg->set_parent (torso);
	class Node	*lower_left_leg = new Node (
			glm::vec3 (1, 0, 0), /* rotation_axis */
			glm::radians (-40.f + 30.f * (slider * 2 - 1)), /* rotation_angle */
			glm::vec3 (0, 1, 1), /* self_origin */
			glm::vec3 (0, -1, 1), /* parent_origin */
			glm::vec3 (0.2f, 1.3f, 0.2f), /* scale */
			model); /* model */
	lower_left_leg->set_parent (left_leg);

	class Node	*right_leg = new Node (
			glm::vec3 (0, 0, 1), /* rotation_axis */
			glm::radians (30.f + 15.f * (slider * -2 + 1)), /* rotation_angle */
			glm::vec3 (-1, 1, 0), /* self_origin */
			glm::vec3 (1, -1, 0), /* parent_origin */
			glm::vec3 (0.2f, 1.3f, 0.2f), /* scale */
			model); /* model */
	right_leg->set_parent (torso);
	class Node	*lower_right_leg = new Node (
			glm::vec3 (1, 0, 0), /* rotation_axis */
			glm::radians (-40.f + 30.f * (slider * 2 - 1)), /* rotation_angle */
			glm::vec3 (0, 1, 1), /* self_origin */
			glm::vec3 (0, -1, 1), /* parent_origin */
			glm::vec3 (0.2f, 1.3f, 0.2f), /* scale */
			model); /* model */
	lower_right_leg->set_parent (right_leg);

	// TODO: cleanup on finishing program
	return torso;
}

static void delete_hierarchy(Node *node) {
	if (!node->childs.empty()) {
		for (auto child : node->childs) {
			delete_hierarchy(child);
		}
	}
	delete node;
}

void delete_human(Node *node) {
	delete_hierarchy(node);
}