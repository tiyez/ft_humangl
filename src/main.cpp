#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "humangl.h"

#include "Skeleton.hpp"
#include "HardSkeleton.hpp"
#include "NodeSerializer.hpp"
#include "MatrixStack.hpp"
#include "Console.hpp"

#include <iostream>
#include <cstring>

extern GLenum error;

int main () {
	Input			input {};
	WindowUserData	userdata = { &input };
	GLFWwindow *window = initialize_glfw(userdata);
	input_register_callbacks(window);
	initialize_opengl();

	RenderObject *cube = initialize_render_object();
	Console	console (cube);
	MatrixStack mstack;

	NodeSerializer	serializer;
	serializer.serialize_nodedata (create_nodedata (cube, "human"));

	while (!glfwWindowShouldClose (window))
	{
		float delta = get_delta();

		if (input.console) {
			input.console = console.listen_command ();
			get_delta ();
		}
		console.update (input, delta);

		ftm::mat4 projection = calculate_projection(window);
		ftm::mat4 camera = calculate_camera(userdata.input, delta);

		Skeleton	&skeleton = console.get_skeleton ();

		// Draw
		mstack.push();
		mstack.transform(projection * camera);
		skeleton.Draw(mstack);
		mstack.pop();
		// Draw end

		bzero (&input.mouse_delta, sizeof input.mouse_delta);
		bzero (&input.print_selected, sizeof input.print_selected);
		bzero (&input.select_node, sizeof input.select_node);
		bzero (&input.select_frame, sizeof input.select_frame);

		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	delete cube;
	glfwTerminate ();
	return (0);
}
