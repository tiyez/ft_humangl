#include "Node.hpp"
#include "MatrixStack.hpp"
#include <functional>

//void draw_node(class MatrixStack &stack, const class Node &node) {
//	stack.push ();
//	if (node.parent) {
//		stack.translate ((node.parent->scale / 2.f) * node.parent_origin);
//	}
//	if (node.rotation_angle != 0) { // TODO(viktor): epsilon
//		stack.rotate (node.rotation_angle, node.rotation_axis);
//	}
//	stack.translate (-((node.scale / 2.f) * node.self_origin));
//	stack.push ();
//	stack.scale (node.scale);
//	draw (stack.top ());
//	stack.pop ();
//	for (auto &child : node.childs) {
//		draw_node (stack, *child);
//	}
//	stack.pop ();
//};

Node *create_human(float slider) {
	class Node	*torso = new Node (
			glm::vec3 (0, 1, 0), /* rotation_axis */
			glm::radians(15.f * (slider * 2 - 1)), /* rotation_angle */
			glm::vec3 (0), /* self_origin */
			glm::vec3 (0), /* parent_origin */
			glm::vec3 (1.3f, 3.14f, 0.8f)); /* scale */

	class Node	*head = new Node (
			glm::vec3 (1, 0, 0), /* rotation_axis */
			glm::radians (15.f * (slider * 2 - 1)), /* rotation_angle */
			glm::vec3 (0, -1, 0), /* self_origin */
			glm::vec3 (0, 1, 0), /* parent_origin */
			glm::vec3 (1)); /* scale */
	head->set_parent (torso);

	// hands
	class Node	*left_hand = new Node (
			glm::vec3 (0, 0, 1), /* rotation_axis */
			glm::radians (-30.f + 15.f * (slider * 2 - 1)), /* rotation_angle */
			glm::vec3 (1, 1, 0), /* self_origin */
			glm::vec3 (-1, 1, 0), /* parent_origin */
			glm::vec3 (0.2f, 1.3f, 0.2f)); /* scale */
	left_hand->set_parent (torso);
	class Node	*lower_left_hand = new Node (
			glm::vec3 (1, 0, 0), /* rotation_axis */
			glm::radians (-40.f + 30.f * (slider * 2 - 1)), /* rotation_angle */
			glm::vec3 (0, 1, 1), /* self_origin */
			glm::vec3 (0, -1, 1), /* parent_origin */
			glm::vec3 (0.2f, 1.3f, 0.2f)); /* scale */
	lower_left_hand->set_parent (left_hand);

	class Node	*right_hand = new Node (
			glm::vec3 (0, 0, 1), /* rotation_axis */
			glm::radians (30.f + 15.f * (slider * -2 + 1)), /* rotation_angle */
			glm::vec3 (-1, 1, 0), /* self_origin */
			glm::vec3 (1, 1, 0), /* parent_origin */
			glm::vec3 (0.2f, 1.3f, 0.2f)); /* scale */
	right_hand->set_parent (torso);
	class Node	*lower_right_hand = new Node (
			glm::vec3 (1, 0, 0), /* rotation_axis */
			glm::radians (-40.f + 30.f * (slider * 2 - 1)), /* rotation_angle */
			glm::vec3 (0, 1, 1), /* self_origin */
			glm::vec3 (0, -1, 1), /* parent_origin */
			glm::vec3 (0.2f, 1.3f, 0.2f)); /* scale */
	lower_right_hand->set_parent (right_hand);

	// legs
	class Node	*left_leg = new Node (
			glm::vec3 (0, 0, 1), /* rotation_axis */
			glm::radians (-30.f + 15.f * (slider * 2 - 1)), /* rotation_angle */
			glm::vec3 (1, 1, 0), /* self_origin */
			glm::vec3 (-1, -1, 0), /* parent_origin */
			glm::vec3 (0.2f, 1.3f, 0.2f)); /* scale */
	left_leg->set_parent (torso);
	class Node	*lower_left_leg = new Node (
			glm::vec3 (1, 0, 0), /* rotation_axis */
			glm::radians (-40.f + 30.f * (slider * 2 - 1)), /* rotation_angle */
			glm::vec3 (0, 1, 1), /* self_origin */
			glm::vec3 (0, -1, 1), /* parent_origin */
			glm::vec3 (0.2f, 1.3f, 0.2f)); /* scale */
	lower_left_leg->set_parent (left_leg);

	class Node	*right_leg = new Node (
			glm::vec3 (0, 0, 1), /* rotation_axis */
			glm::radians (30.f + 15.f * (slider * -2 + 1)), /* rotation_angle */
			glm::vec3 (-1, 1, 0), /* self_origin */
			glm::vec3 (1, -1, 0), /* parent_origin */
			glm::vec3 (0.2f, 1.3f, 0.2f)); /* scale */
	right_leg->set_parent (torso);
	class Node	*lower_right_leg = new Node (
			glm::vec3 (1, 0, 0), /* rotation_axis */
			glm::radians (-40.f + 30.f * (slider * 2 - 1)), /* rotation_angle */
			glm::vec3 (0, 1, 1), /* self_origin */
			glm::vec3 (0, -1, 1), /* parent_origin */
			glm::vec3 (0.2f, 1.3f, 0.2f)); /* scale */
	lower_right_leg->set_parent (right_leg);

	return torso;
}