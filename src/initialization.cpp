#include <iostream>
#include <glad/glad.h>

#include "humangl.h"
#include "def.h"

GLenum error;

static void	error_callback(int error, const char* description) {
	std::cerr << "Error(" << error << "): " << description << std::endl;
}

GLFWwindow *initialize_glfw(WindowUserData&	userdata) {
	if (!glfwInit ()) {
		std::cerr << "failed to initialize GLFW" << std::endl;
		ExitFatal();
	}

	glfwSetErrorCallback (error_callback);

	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow	*window = glfwCreateWindow (1000, 600, "humangl", 0, 0);
	if (!window) {
		std::cerr << "cannot create a window" << std::endl;
		ExitFatal();
	}

	glfwSetWindowUserPointer (window, static_cast<void *>(&userdata));
	glfwMakeContextCurrent (window);
	gladLoadGLLoader ((void *(*)(const char *)) glfwGetProcAddress);

	glfwSwapInterval (1);

	return window;
}

void initialize_opengl(void) {
	std::cerr << "OpenGL " << glGetString(GL_VERSION) << ", GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	GL (glEnable (GL_CULL_FACE));
	GL (glFrontFace (GL_CCW));
	GL (glClearColor (1, 1, 1, 1));
	GL (glEnable (GL_DEPTH_TEST));
	GL (glDepthFunc (GL_LESS));
}


// buffer and vao is not returned because they don't need in program
int initialize_buffers(void) {
	struct vertex {
		float	pos[3];
		float	color[4];
	};

	struct vertex verticies_cube[] = {
		#define Repos(X) ((X) - 0.5f)
		#define Quad(x1,y1,z1, x2,y2,z2, x3,y3,z3, x4,y4,z4,  c1,c2,c3) \
		{ { Repos(x1), Repos(y1), Repos(z1) }, { c1, c2, c3, 1 } }, \
		{ { Repos(x2), Repos(y2), Repos(z2) }, { c1, c2, c3, 1 } }, \
		{ { Repos(x3), Repos(y3), Repos(z3) }, { c1, c2, c3, 1 } }, \
		{ { Repos(x1), Repos(y1), Repos(z1) }, { c1, c2, c3, 1 } }, \
		{ { Repos(x3), Repos(y3), Repos(z3) }, { c1, c2, c3, 1 } }, \
		{ { Repos(x4), Repos(y4), Repos(z4) }, { c1, c2, c3, 1 } }

			Quad (0,0,0, 0,1,0, 1,1,0, 1,0,0,  0,0,1),
					Quad (0,0,1, 1,0,1, 1,1,1, 0,1,1,  0,0,1),
					Quad (0,0,0, 0,0,1, 0,1,1, 0,1,0,  1,0,0),
					Quad (1,0,0, 1,1,0, 1,1,1, 1,0,1,  1,0,0),
					Quad (0,0,0, 1,0,0, 1,0,1, 0,0,1,  0,1,0),
					Quad (0,1,0, 0,1,1, 1,1,1, 1,1,0,  0,1,0),

		#undef Quad
		#undef Repos
		};

	GLuint	vao;
	GL (glGenVertexArrays (1, &vao));
	GL (glBindVertexArray (vao));

	GLuint	buffer;
	GL (glGenBuffers (1, &buffer));
	GL (glBindBuffer (GL_ARRAY_BUFFER, buffer));
	GL (glBufferData (GL_ARRAY_BUFFER, sizeof verticies_cube, verticies_cube, GL_STATIC_DRAW));
	GL (glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, sizeof verticies_cube[0], 0));
	GL (glVertexAttribPointer (1, 4, GL_FLOAT, GL_FALSE, sizeof verticies_cube[0], Member_Offset (struct vertex, color)));
	GL (glEnableVertexAttribArray (0));
	GL (glEnableVertexAttribArray (1));

	return Array_Count(verticies_cube);
}
