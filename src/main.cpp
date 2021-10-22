#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "humangl.h"

#include "Skeleton.hpp"
#include "MatrixStack.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

extern GLenum error;

int main () {
	Input			input {};
	WindowUserData	userdata = { &input };
	GLFWwindow *window = initialize_glfw(userdata);
	input_register_callbacks(window);
	initialize_opengl();

	RenderObject *cube = initialize_render_object();
	Skeleton human = Skeleton(cube);
	MatrixStack mstack;

	while (!glfwWindowShouldClose (window))
	{
		float delta = get_delta();

		glm::mat4 projection = calculate_projection(window);
		glm::mat4 camera = calculate_camera(userdata.input, delta);

		human.SelectNode(input.node_selected);
		human.ChangeSizeSelected(input.scale_delta);
		human.ChangeColorSelected(input.color_delta);
		if (userdata.input->print_selected) {
			human.PrintSelectedNode();
		}

		// Draw
		mstack.push();
		mstack.transform(projection * camera);
		if (!userdata.input->animate) {
			human.Animate(delta);
		}
		human.Draw(mstack);
		mstack.pop();
		// Draw end

		memset (&input.mouse_delta, 0, sizeof input.mouse_delta);
		memset (&input.print_selected, 0, sizeof input.print_selected);

		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	delete cube;
	glfwTerminate ();
	return (0);
}
