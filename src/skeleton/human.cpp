#include "Node.hpp"

static std::vector<RotationFrame> get_human_torso_rot_frames() {
	std::vector<RotationFrame> rframes;

	rframes.push_back({ 0.f, glm::vec3 (0, 1, 0), glm::radians(-15.f)});
	rframes.push_back({0.5f, glm::vec3 (0, 1, 0), glm::radians(15.f)});
	rframes.push_back({ 3.f, glm::vec3 (0, 1, 0), glm::radians(-15.f)});

	return rframes;
}

static std::vector<RotationFrame> get_human_head_rot_frames() {
	std::vector<RotationFrame> rframes;

	rframes.push_back({ 0.f, glm::vec3 (1, 0, 0), glm::radians(-15.f)});
	rframes.push_back({1.0f, glm::vec3 (1, 0, 0), glm::radians(15.f)});
	rframes.push_back({ 3.f, glm::vec3 (1, 0, 0), glm::radians(-15.f)});

	return rframes;
}

static std::vector<RotationFrame> get_human_left_hand_rot_frames() {
	std::vector<RotationFrame> rframes;

	rframes.push_back({ 0.f, glm::vec3 (0, 0, 1), glm::radians(0.f)});
	rframes.push_back({1.0f, glm::vec3 (0, 0, 1), glm::radians(-30.f)});
	rframes.push_back({ 3.f, glm::vec3 (0, 0, 1), glm::radians(0.f)});

	return rframes;
}

static std::vector<RotationFrame> get_human_right_hand_rot_frames() {
	std::vector<RotationFrame> rframes;

	rframes.push_back({ 0.f, glm::vec3 (0, 0, 1), glm::radians(0.f)});
	rframes.push_back({1.0f, glm::vec3 (0, 0, 1), glm::radians(30.f)});
	rframes.push_back({ 3.f, glm::vec3 (0, 0, 1), glm::radians(0.f)});

	return rframes;
}

static std::vector<RotationFrame> get_human_lower_left_hand_rot_frames() {
	std::vector<RotationFrame> rframes;

	rframes.push_back({ 0.f, glm::vec3 (1, 0, 0), glm::radians(0.f)});
	rframes.push_back({1.0f, glm::vec3 (1, 0, 0), glm::radians(-120.f)});
	rframes.push_back({ 3.f, glm::vec3 (1, 0, 0), glm::radians(0.f)});

	return rframes;
}


static std::vector<RotationFrame> get_human_lower_right_hand_rot_frames() {
	std::vector<RotationFrame> rframes;

	rframes.push_back({ 0.f, glm::vec3 (1, 0, 0), glm::radians(0.f)});
	rframes.push_back({1.0f, glm::vec3 (1, 0, 0), glm::radians(-120.f)});
	rframes.push_back({ 3.f, glm::vec3 (1, 0, 0), glm::radians(0.f)});

	return rframes;
}

static std::vector<RotationFrame> get_human_left_leg_rot_frames() {
	std::vector<RotationFrame> rframes;

	rframes.push_back({ 0.f, glm::vec3 (1, 0, 0), glm::radians(0.f)});
	rframes.push_back({1.0f, glm::vec3 (1, 0, 0), glm::radians(-110.f)});
	rframes.push_back({ 3.f, glm::vec3 (1, 0, 0), glm::radians(0.f)});

	return rframes;
}

static std::vector<RotationFrame> get_human_right_leg_rot_frames() {
	std::vector<RotationFrame> rframes;

	rframes.push_back({ 0.f, glm::vec3 (1, 0, 0), glm::radians(0.f)});
	rframes.push_back({1.0f, glm::vec3 (1, 0, 0), glm::radians(-110.f)});
	rframes.push_back({ 3.f, glm::vec3 (1, 0, 0), glm::radians(0.f)});

	return rframes;
}

static std::vector<RotationFrame> get_human_lower_left_leg_rot_frames() {
	std::vector<RotationFrame> rframes;

	rframes.push_back({ 0.f, glm::vec3 (1, 0, 0), glm::radians(0.f)});
	rframes.push_back({1.0f, glm::vec3 (1, 0, 0), glm::radians(160.f)});
	rframes.push_back({ 3.f, glm::vec3 (1, 0, 0), glm::radians(0.f)});

	return rframes;
}


static std::vector<RotationFrame> get_human_lower_right_leg_rot_frames() {
	std::vector<RotationFrame> rframes;

	rframes.push_back({ 0.f, glm::vec3 (1, 0, 0), glm::radians(0.f)});
	rframes.push_back({1.0f, glm::vec3 (1, 0, 0), glm::radians(160.f)});
	rframes.push_back({ 3.f, glm::vec3 (1, 0, 0), glm::radians(0.f)});

	return rframes;
}

Node *create_human(const RenderObject *model) {
	Node *torso = new Node (
			glm::vec3 (0),						/* translation */
			glm::quat (),								/* rotation */
			glm::vec3 (1.3f, 3.14f, 0.8f),		/* scale */
			glm::vec3 (0),						/* self_origin */
			glm::vec3 (0),					/* parent_origin */
			model);												/* model */
	torso->SetRotationFrames(get_human_torso_rot_frames());
	torso->color = glm::vec3 (0.6, 0.8, 0.2);


	Node *head = new Node (
			glm::vec3 (0),						/* translation */
			glm::quat (),								/* rotation */
			glm::vec3 (1),							/* scale */
			glm::vec3 (0, -1, 0),			/* self_origin */
			glm::vec3 (0, 1, 0),			/* parent_origin */
			model);												/* model */
	head->SetRotationFrames(get_human_head_rot_frames());
	head->selected = true;
	head->SetParent(torso);

	// hands
	Node *left_hand = new Node (
			glm::vec3 (0),						/* translation */
			glm::quat (),								/* rotation */
			glm::vec3 (0.1f, 1.3f, 0.2f),		/* scale */
			glm::vec3 (1, 1, 0),			/* self_origin */
			glm::vec3 (-1, 1, 0),		/* parent_origin */
			model);
	left_hand->SetRotationFrames(get_human_left_hand_rot_frames());
	left_hand->SetParent(torso);

	Node *lower_left_hand = new Node (
			glm::vec3 (0),						/* translation */
			glm::quat (),								/* rotation */
			glm::vec3 (0.1f, 1.3f, 0.2f),		/* scale */
			glm::vec3 (0, 1, 0),			/* self_origin */
			glm::vec3 (0, -1, 0),		/* parent_origin */
			model);
	lower_left_hand->SetRotationFrames(get_human_lower_left_hand_rot_frames());
	lower_left_hand->SetParent(left_hand);

	Node *right_hand = new Node (
			glm::vec3 (0),						/* translation */
			glm::quat (),								/* rotation */
			glm::vec3 (0.1f, 1.3f, 0.2f),		/* scale */
			glm::vec3 (-1, 1, 0),			/* self_origin */
			glm::vec3 (1, 1, 0),		/* parent_origin */
			model);
	right_hand->SetRotationFrames(get_human_right_hand_rot_frames());
	right_hand->SetParent(torso);

	Node *lower_right_hand = new Node (
			glm::vec3 (0),						/* translation */
			glm::quat (),								/* rotation */
			glm::vec3 (0.1f, 1.3f, 0.2f),		/* scale */
			glm::vec3 (0, 1, 0),			/* self_origin */
			glm::vec3 (0, -1, 0),		/* parent_origin */
			model);
	lower_right_hand->SetRotationFrames(get_human_lower_right_hand_rot_frames());
	lower_right_hand->SetParent(right_hand);

	Node *left_leg = new Node (
			glm::vec3 (0),						/* translation */
			glm::quat (),								/* rotation */
			glm::vec3 (0.1f, 1.3f, 0.2f),		/* scale */
			glm::vec3 (0, 1, 0),			/* self_origin */
			glm::vec3 (-1, -1, 0),		/* parent_origin */
			model);
	left_leg->SetParent(torso);
	left_leg->SetRotationFrames(get_human_left_leg_rot_frames());

	Node *right_leg = new Node (
			glm::vec3 (0),						/* translation */
			glm::quat (),								/* rotation */
			glm::vec3 (0.1f, 1.3f, 0.2f),		/* scale */
			glm::vec3 (0, 1, 0),			/* self_origin */
			glm::vec3 (1, -1, 0),		/* parent_origin */
			model);
	right_leg->SetParent(torso);
	right_leg->SetRotationFrames(get_human_right_leg_rot_frames());


	Node *lower_left_leg = new Node (
			glm::vec3 (0),						/* translation */
			glm::quat (),								/* rotation */
			glm::vec3 (0.1f, 1.3f, 0.2f),		/* scale */
			glm::vec3 (0, 1, 0),			/* self_origin */
			glm::vec3 (0, -1, 0),		/* parent_origin */
			model);
	lower_left_leg->SetParent(left_leg);
	lower_left_leg->SetRotationFrames(get_human_lower_left_leg_rot_frames());

	Node *lower_right_leg = new Node (
			glm::vec3 (0),						/* translation */
			glm::quat (),								/* rotation */
			glm::vec3 (0.1f, 1.3f, 0.2f),		/* scale */
			glm::vec3 (0, 1, 0),			/* self_origin */
			glm::vec3 (0, -1, 0),		/* parent_origin */
			model);
	lower_right_leg->SetParent(right_leg);
	lower_right_leg->SetRotationFrames(get_human_lower_right_leg_rot_frames());

	return torso;
}