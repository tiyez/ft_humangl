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

// TODO: make normal camera location ))
// TODO: remove redundant output
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
	std::cout << serializer.finalize () << std::endl;


	while (!glfwWindowShouldClose (window))
	{
		float delta = get_delta();

		if (input.console) {
			input.console = console.listen_command ();
			get_delta ();
		}
		console.update (input, delta);

		ftm::mat4 projection_t = calculate_projection(window);
//		std::cout << projection_t << std::endl;
		glm::mat4 projection = (glm::mat4)projection_t;

		ftm::mat4 camera_t = calculate_camera(userdata.input, delta);
		glm::mat4 camera = (glm::mat4)camera_t;
//		std::cout << camera << std::endl;


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

		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	delete cube;
	glfwTerminate ();
	return (0);
}
