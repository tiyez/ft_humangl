#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "humangl.h"

#include "Skeleton.hpp"
#include "MatrixStack.hpp"

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
	Skeleton human = Skeleton(cube);
	MatrixStack mstack;

	while (!glfwWindowShouldClose (window))
	{
		float delta = get_delta();

		glm::mat4 projection = calculate_projection(window);
		glm::mat4 camera = calculate_camera(userdata.input, delta);

		mstack.push();
		mstack.transform(projection * camera);
		human.Animate(delta);
		human.Draw(mstack);
		mstack.pop();

		memset (&input.mouse_delta, 0, sizeof input.mouse_delta);
		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	delete cube;
	glfwTerminate ();
	return (0);
}


