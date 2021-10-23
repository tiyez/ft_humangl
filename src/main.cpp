#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "humangl.h"

#include "Skeleton.hpp"
#include "HardSkeleton.hpp"
#include "NodeSerializer.hpp"
#include "MatrixStack.hpp"
#include "Console.hpp"

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
	Console	console (Skeleton (create_nodedata (cube, "human")));
	MatrixStack mstack;

	NodeSerializer	serializer;
	serializer.serialize_nodedata (create_nodedata (cube, "human"));
	std::cout << serializer.finalize () << std::endl;


	while (!glfwWindowShouldClose (window))
	{
		float delta = get_delta();

		if (input.console) {
			console.listen_command ();
			get_delta ();
		}
		console.update (input, delta);

		glm::mat4 projection = calculate_projection(window);
		glm::mat4 camera = calculate_camera(userdata.input, delta);

		Skeleton	&skeleton = console.get_skeleton ();

		// Draw
		mstack.push();
		mstack.transform(projection * camera);
		skeleton.Draw(mstack);
		mstack.pop();
		// Draw end

		memset (&input.mouse_delta, 0, sizeof input.mouse_delta);
		memset (&input.print_selected, 0, sizeof input.print_selected);
		memset (&input.select_node, 0, sizeof input.select_node);
		memset (&input.select_frame, 0, sizeof input.select_frame);
		memset (&input.rotate_x, 0, sizeof input.rotate_x);
		memset (&input.rotate_y, 0, sizeof input.rotate_y);

		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	delete cube;
	glfwTerminate ();
	return (0);
}
