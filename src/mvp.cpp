#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "def.h"
#include "ftm.hpp"
#include "humangl.h"

extern GLenum error;

ftm::mat4 calculate_projection(GLFWwindow *window) {
	int width, height;
	glfwGetFramebufferSize (window, &width, &height);
	GL (glViewport (0, 0, width, height));
	GL (glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	return ftm::infinitePerspective (ftm::radians (60.f), (float) width / height, 0.1f);
}

ftm::mat4 calculate_camera(Input *input, float delta) {
	const float			movement_speed = 3.0f;
	const float			rotation_speed = 0.1f;
	static ftm::vec3	camera_forward(1, 0, 1);
	static ftm::vec3	camera_position(7, 0, 9);

	ftm::vec3	camera_right = ftm::normalize (ftm::cross (ftm::vec3 (0, 1, 0), camera_forward));
	ftm::vec3	camera_forward_plane = ftm::normalize (ftm::cross (camera_right, ftm::vec3 (0, 1, 0)));

	camera_position += camera_forward_plane * (-input->movement_delta.z * delta * movement_speed);
	camera_position += camera_right * (input->movement_delta.x * delta * movement_speed);
	camera_position.y += input->movement_delta.y * delta * movement_speed;

	camera_forward = ftm::rotateY (camera_forward, -input->mouse_delta.x * delta * rotation_speed);
	camera_forward = ftm::rotate (camera_forward, -input->mouse_delta.y * delta * rotation_speed, camera_right);
	camera_forward = ftm::normalize (camera_forward);

	return ftm::lookAt (camera_position, camera_position - camera_forward, ftm::vec3 (0, 1, 0));
}