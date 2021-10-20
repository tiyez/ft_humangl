#include "Node.hpp"

Node *create_human(float slider, RenderObject *model) {

/* lation */
/* rotation */
/* scale */
/* self_origin */
/* parent_origin */
/* model */

	Node *torso = new Node (
			glm::vec3 (0),																					/* lation */
			glm::angleAxis(glm::radians(15.f * (slider * 2) -1), glm::vec3(0, 1, 0)),	/* rotation */
			glm::vec3 (1.3f, 3.14f, 0.8f),																	/* scale */
			glm::vec3 (0),																					/* self_origin */
			glm::vec3 (0),																				/* parent_origin */
			model);																											/* model */

//	class Node	*torso = new Node (
//			glm::vec3 (0, 1, 0), /* rotation_axis */
//			glm::radians(15.f * (slider * 2 - 1)), /* rotation_angle */
//			glm::vec3 (0), /* self_origin */
//			glm::vec3 (0), /* parent_origin */
//			glm::vec3 (1.3f, 3.14f, 0.8f), /* scale */
//			model); /* model */
//
//	class Node	*head = new Node (
//			glm::vec3 (1, 0, 0), /* rotation_axis */
//			glm::radians (15.f * (slider * 2 - 1)), /* rotation_angle */
//			glm::vec3 (0, -1, 0), /* self_origin */
//			glm::vec3 (0, 1, 0), /* parent_origin */
//			glm::vec3 (1),  /* scale */
//			model); /* model */
//	head->SetParent(torso);
//
//	// hands
//	class Node	*left_hand = new Node (
//			glm::vec3 (0, 0, 1), /* rotation_axis */
//			glm::radians (-30.f + 15.f * (slider * 2 - 1)), /* rotation_angle */
//			glm::vec3 (1, 1, 0), /* self_origin */
//			glm::vec3 (-1, 1, 0), /* parent_origin */
//			glm::vec3 (0.2f, 1.3f, 0.2f), /* scale */
//			model);  /* model */
//	left_hand->SetParent(torso);
//	class Node	*lower_left_hand = new Node (
//			glm::vec3 (1, 0, 0), /* rotation_axis */
//			glm::radians (-40.f + 30.f * (slider * 2 - 1)), /* rotation_angle */
//			glm::vec3 (0, 1, 1), /* self_origin */
//			glm::vec3 (0, -1, 1), /* parent_origin */
//			glm::vec3 (0.2f, 1.3f, 0.2f), /* scale */
//			model);  /* model */
//	lower_left_hand->SetParent(left_hand);
//
//	class Node	*right_hand = new Node (
//			glm::vec3 (0, 0, 1), /* rotation_axis */
//			glm::radians (30.f + 15.f * (slider * -2 + 1)), /* rotation_angle */
//			glm::vec3 (-1, 1, 0), /* self_origin */
//			glm::vec3 (1, 1, 0), /* parent_origin */
//			glm::vec3 (0.2f, 1.3f, 0.2f), /* scale */
//			model); /* model */
//	right_hand->SetParent(torso);
//	class Node	*lower_right_hand = new Node (
//			glm::vec3 (1, 0, 0), /* rotation_axis */
//			glm::radians (-40.f + 30.f * (slider * 2 - 1)), /* rotation_angle */
//			glm::vec3 (0, 1, 1), /* self_origin */
//			glm::vec3 (0, -1, 1), /* parent_origin */
//			glm::vec3 (0.2f, 1.3f, 0.2f), /* scale */
//			model); /* model */
//	lower_right_hand->SetParent(right_hand);
//
//	// legs
//	class Node	*left_leg = new Node (
//			glm::vec3 (0, 0, 1), /* rotation_axis */
//			glm::radians (-30.f + 15.f * (slider * 2 - 1)), /* rotation_angle */
//			glm::vec3 (1, 1, 0), /* self_origin */
//			glm::vec3 (-1, -1, 0), /* parent_origin */
//			glm::vec3 (0.2f, 1.3f, 0.2f), /* scale */
//			model); /* model */
//	left_leg->SetParent(torso);
//	class Node	*lower_left_leg = new Node (
//			glm::vec3 (1, 0, 0), /* rotation_axis */
//			glm::radians (-40.f + 30.f * (slider * 2 - 1)), /* rotation_angle */
//			glm::vec3 (0, 1, 1), /* self_origin */
//			glm::vec3 (0, -1, 1), /* parent_origin */
//			glm::vec3 (0.2f, 1.3f, 0.2f), /* scale */
//			model); /* model */
//	lower_left_leg->SetParent(left_leg);
//
//	class Node	*right_leg = new Node (
//			glm::vec3 (0, 0, 1), /* rotation_axis */
//			glm::radians (30.f + 15.f * (slider * -2 + 1)), /* rotation_angle */
//			glm::vec3 (-1, 1, 0), /* self_origin */
//			glm::vec3 (1, -1, 0), /* parent_origin */
//			glm::vec3 (0.2f, 1.3f, 0.2f), /* scale */
//			model); /* model */
//	right_leg->SetParent(torso);
//	class Node	*lower_right_leg = new Node (
//			glm::vec3 (1, 0, 0), /* rotation_axis */
//			glm::radians (-40.f + 30.f * (slider * 2 - 1)), /* rotation_angle */
//			glm::vec3 (0, 1, 1), /* self_origin */
//			glm::vec3 (0, -1, 1), /* parent_origin */
//			glm::vec3 (0.2f, 1.3f, 0.2f), /* scale */
//			model); /* model */
//	lower_right_leg->SetParent(right_leg);

	return torso;
}

void delete_human(Node *node) {
	delete_hierarchy(node);
}