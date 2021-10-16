
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "def.h"

GLenum error;

static void	error_callback(int error, const char* description) {
	std::cerr << "Error(" << error << "): " << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

static void	mouse_pos_callback (GLFWwindow *window, double x, double y) {

}

int main () {
	if (!glfwInit ()) {
		std::cerr << "failed to initialize GLFW" << std::endl;
		return -1;
	}

	glfwSetErrorCallback (error_callback);

	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow	*window = glfwCreateWindow (1000, 600, "humangl", 0, 0);
	if (!window) {
		std::cerr << "cannot create a window" << std::endl;
		return -1;
	}

	// struct input input = {0};
	// glfwSetWindowUserPointer (window, &input);

	glfwMakeContextCurrent (window);
	gladLoadGLLoader ((void *(*)(const char *)) glfwGetProcAddress);

	// glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback (window, key_callback);
	glfwSetCursorPosCallback (window, mouse_pos_callback);

	std::cerr << "OpenGL " << glGetString(GL_VERSION) << ", GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	glfwSwapInterval (1);

	GL (glEnable (GL_CULL_FACE));
	GL (glFrontFace (GL_CCW));
	GL (glClearColor (1, 1, 1, 1));
	GL (glEnable (GL_DEPTH_TEST));
	GL (glDepthFunc (GL_LESS));

	double last_frame_time = glfwGetTime ();
	double time;
	double delta;

	while (!glfwWindowShouldClose (window))
	{
		time = glfwGetTime ();
		delta = time - last_frame_time;
		last_frame_time = time;

		int width, height;
		glfwGetFramebufferSize (window, &width, &height);
		GL (glViewport (0, 0, width, height));
		GL (glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	glfwTerminate ();
	return (0);
}


