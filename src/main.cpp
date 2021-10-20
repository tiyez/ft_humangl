#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "humangl.h"

#include "Skeleton.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

extern GLenum error;

int main () {
	Input			input;
	WindowUserData	userdata = { &input };
	GLFWwindow *window = initialize_glfw(userdata);
	input_register_callbacks(window);
	initialize_opengl();

	RenderObject *cube = initialize_render_object();

	while (!glfwWindowShouldClose (window))
	{
		float delta = get_delta();
		float slider = get_slider(delta);

		glm::mat4 projection = calculate_projection(window);
		glm::mat4 camera = calculate_camera(userdata.input, delta);

		Skeleton human = Skeleton(cube, slider); // TODO: add animation choice
		human.draw(projection * camera);

		memset (&input.mouse_delta, 0, sizeof input.mouse_delta);
		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	delete cube;
	glfwTerminate ();
	return (0);
}


