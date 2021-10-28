#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "ftm.hpp"

#include "def.h"
#include "humangl.h"

extern GLenum error;

// TODO: remove this after evaluation
std::ostream &operator<<(std::ostream &o, const glm::vec3 &v);
std::ostream &operator<<(std::ostream &o, const ftm::vec3 &v);
std::ostream &operator<<(std::ostream &o, const glm::mat4 &mat);

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
	static ftm::vec3	camera_forward(0, 0, 1);
	static glm::vec3	camera_forward_g(0, 0, 1);
	static ftm::vec3	camera_position(0, 0, 2);
	static glm::vec3	camera_position_g(0, 0, 2);

//	ftm::vec3 tf = ftm::cross (ftm::vec3 (0, 1, 0), camera_forward);
//	glm::vec3 tg = glm::cross (glm::vec3 (0, 1, 0), camera_forward_g);

//	std::cout << "cross f: " << tf << std::endl;
//	std::cout << "cross g: " << tg << std::endl;

	ftm::vec3	camera_right = ftm::normalize (ftm::cross (ftm::vec3 (0, 1, 0), camera_forward));
	glm::vec3	camera_right_g = glm::normalize (glm::cross (glm::vec3 (0, 1, 0), camera_forward_g));

//	std::cout << "g: " << camera_right_g << std::endl;
//	std::cout << "f: " << camera_right << std::endl;

	ftm::vec3	camera_forward_plane = ftm::normalize (ftm::cross (camera_right, ftm::vec3 (0, 1, 0)));
	glm::vec3	camera_forward_plane_g = glm::normalize (glm::cross (camera_right_g, glm::vec3 (0, 1, 0)));

//	std::cout << "forward plane g: " << camera_forward_plane << std::endl;
//	std::cout << "forward plane f: " << camera_forward_plane_g << std::endl;

	camera_position += camera_forward_plane * (-input->movement_delta.z * delta * movement_speed);
	camera_position_g += camera_forward_plane_g * (-input->movement_delta.z * delta * movement_speed);

//	std::cout << "camera position g: " << camera_position << std::endl;
//	std::cout << "camera position f: " << camera_position_g << std::endl;

	camera_position += camera_right * (input->movement_delta.x * delta * movement_speed);
	camera_position_g += camera_right_g * (input->movement_delta.x * delta * movement_speed);

//	std::cout << "camera position g: " << camera_position << std::endl;
//	std::cout << "camera position f: " << camera_position_g << std::endl;

	camera_position.y += input->movement_delta.y * delta * movement_speed;
	camera_position_g.y += input->movement_delta.y * delta * movement_speed;

//	std::cout << "camera position g: " << camera_position << std::endl;
//	std::cout << "camera position f: " << camera_position_g << std::endl;

	camera_forward = ftm::rotateY (camera_forward, -input->mouse_delta.x * delta * rotation_speed);
	camera_forward_g = glm::rotateY (camera_forward_g, -input->mouse_delta.x * delta * rotation_speed);

//	std::cout << "camera forward g: " << camera_forward << std::endl;
//	std::cout << "camera forward f: " << camera_forward_g << std::endl;

	camera_forward = ftm::rotate (camera_forward, -input->mouse_delta.y * delta * rotation_speed, camera_right);
	camera_forward_g = glm::rotate (camera_forward_g, -input->mouse_delta.y * delta * rotation_speed, camera_right_g);

//	std::cout << "camera forward g: " << camera_forward << std::endl;
//	std::cout << "camera forward f: " << camera_forward_g << std::endl;

	camera_forward = ftm::normalize (camera_forward);
	camera_forward_g = glm::normalize (camera_forward_g);

//	std::cout << "camera forward g: " << camera_forward << std::endl;
//	std::cout << "camera forward f: " << camera_forward_g << std::endl;

//	std::cout << camera_position << std::endl;
//	std::cout << camera_forward << std::endl;

//	std::cout << "cam pos g: " << camera_position_g << std::endl;
//	std::cout << "cam pos f: " << camera_position << std::endl;
//
//	std::cout << "cam dir g: " << camera_position_g - camera_forward_g << std::endl;
//	std::cout << "cam dir f: " << camera_position - camera_forward << std::endl;

	glm::mat4 look_g = glm::lookAt (camera_position_g, camera_position_g - camera_forward_g, glm::vec3 (0, 1, 0));
	(void)look_g;
	ftm::mat4 look = ftm::lookAt (camera_position, camera_position - camera_forward, ftm::vec3 (0, 1, 0));

	std::cout << "look g: \n" << look_g << std::endl;
	std::cout << "look f: \n" << (glm::mat4)look << std::endl;

	return look;
}