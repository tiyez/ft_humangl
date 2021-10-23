#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "def.h"
#include "humangl.h"

extern GLenum error;

glm::mat4 calculate_projection(GLFWwindow *window) {
	int width, height;
	glfwGetFramebufferSize (window, &width, &height);
	GL (glViewport (0, 0, width, height));
	GL (glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	return glm::infinitePerspective (glm::radians (60.f), (float) width / height, 0.1f);
}

glm::mat4 calculate_camera(Input *input, float delta) {
	const float			movement_speed = 3.0f;
	const float			rotation_speed = 0.1f;
	static glm::vec3	camera_forward(0, 0, 1);
	static glm::vec3	camera_position(0, 0, 2);

	glm::vec3	camera_right = glm::normalize (glm::cross (glm::vec3 (0, 1, 0), camera_forward));
	glm::vec3	camera_forward_plane = glm::normalize (glm::cross (camera_right, glm::vec3 (0, 1, 0)));
	camera_position += camera_forward_plane * (-input->movement_delta.z * delta * movement_speed);
	camera_position += camera_right * (input->movement_delta.x * delta * movement_speed);
	camera_position.y += input->movement_delta.y * delta * movement_speed;

	camera_forward = glm::rotateY (camera_forward, -input->mouse_delta.x * delta * rotation_speed);
	camera_forward = glm::rotate (camera_forward, -input->mouse_delta.y * delta * rotation_speed, camera_right);
	camera_forward = glm::normalize (camera_forward);

	return glm::lookAt (camera_position, camera_position - camera_forward, glm::vec3 (0, 1, 0));
}