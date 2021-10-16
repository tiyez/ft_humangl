
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "def.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

GLenum error;

struct Input {
	glm::vec3	movement_delta;
	glm::vec2	mouse_position;
	glm::vec2	mouse_delta;
};

struct WindowUserData {
	struct Input	*input;
};

static void	error_callback(int error, const char* description) {
	std::cerr << "Error(" << error << "): " << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	WindowUserData	*userdata = static_cast<WindowUserData *>(glfwGetWindowUserPointer (window));
	Input			*input = userdata->input;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_D: { input->movement_delta.x += 1; } break ;
			case GLFW_KEY_A: { input->movement_delta.x += -1; } break ;
			case GLFW_KEY_W: { input->movement_delta.z += 1; } break ;
			case GLFW_KEY_S: { input->movement_delta.z += -1; } break ;
			case GLFW_KEY_E: { input->movement_delta.y += 1; } break ;
			case GLFW_KEY_Q: { input->movement_delta.y += -1; } break ;
		}
	} else if (action == GLFW_RELEASE) {
		switch (key) {
			case GLFW_KEY_D: { input->movement_delta.x -= 1; } break ;
			case GLFW_KEY_A: { input->movement_delta.x -= -1; } break ;
			case GLFW_KEY_W: { input->movement_delta.z -= 1; } break ;
			case GLFW_KEY_S: { input->movement_delta.z -= -1; } break ;
			case GLFW_KEY_E: { input->movement_delta.y -= 1; } break ;
			case GLFW_KEY_Q: { input->movement_delta.y -= -1; } break ;
		}
	}
}

static void	mouse_pos_callback (GLFWwindow *window, double x, double y) {
	WindowUserData	*userdata = static_cast<WindowUserData *>(glfwGetWindowUserPointer (window));
	Input			*input = userdata->input;

	if (glm::abs (x - input->mouse_position.x) < 100 && glm::abs (y - input->mouse_position.y) < 100) {
		input->mouse_delta.x = x - input->mouse_position.x;
		input->mouse_delta.y = y - input->mouse_position.y;
	} else {
		input->mouse_delta.x = 0;
		input->mouse_delta.y = 0;
	}
	input->mouse_position.x = x;
	input->mouse_position.y = y;
}


GLuint	new_shader_object (const char *source, GLenum kind) {
	GLuint	handle;
	GLint	success;

	GL (handle = glCreateShader (kind));
	GL (glShaderSource (handle, 1, &source, 0));
	GL (glCompileShader (handle));
	GL (glGetShaderiv (handle, GL_COMPILE_STATUS, &success));
	if (success == GL_FALSE) {
		char	message[32 * 1024];
		GLint	len;

		GL (glGetShaderInfoLog (handle, sizeof message - 1, &len, message));
		message[len] = 0;
		Debug ("Shader Compilation Error:\n%s", message);
		GL (glDeleteShader (handle));
		handle = 0;
	}
	return (handle);
}

const char	*get_default_vertex_shader (void) {
	return (
		"#version 410\n"

		"in vec3 v_pos;\n"
		"in vec4 v_color;\n"
		"out vec4 f_color;\n"
		"uniform mat4 MVP;\n"

		"void main () {\n"
			"f_color = v_color;\n"
			"gl_Position = MVP * vec4(v_pos, 1);\n"
		"}\n"
	);
}

const char	*get_default_fragment_shader (void) {
	return (
		"#version 410\n"

		"in vec4 f_color;\n"
		"out vec4 _color;\n"
		"uniform sampler2D u_tex;\n"

		"void main () {\n"
			"_color = f_color;\n"
		"}\n"
	);
}

GLuint	new_shader_program (const char *vertex_source, const char *fragment_source) {
	GLuint	program, vertex, fragment;

	program = 0;
	vertex = new_shader_object (vertex_source, GL_VERTEX_SHADER);
	if (vertex != 0) {
		fragment = new_shader_object (fragment_source, GL_FRAGMENT_SHADER);
		if (fragment != 0) {
			GLint	linked;

			GL (program = glCreateProgram ());
			GL (glAttachShader (program, vertex));
			GL (glAttachShader (program, fragment));
			GL (glLinkProgram (program));
			GL (glGetProgramiv (program, GL_LINK_STATUS, &linked));
			if (linked == GL_FALSE) {
				char	message[32 * 1024];
				GLint	len;

				GL (glGetProgramInfoLog (program, sizeof message - 1, &len, message));
				Debug ("Program Linkage Error:\n%s", message);
				GL (glDeleteProgram (program));
				program = 0;
			} else {
				GL (glDetachShader (program, vertex));
				GL (glDetachShader (program, fragment));
			}
			GL (glDeleteShader (fragment));
			fragment = 0;
		}
		GL (glDeleteShader (vertex));
		vertex = 0;
	}
	return (program);
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

	Input			input;
	WindowUserData	userdata = { &input };
	glfwSetWindowUserPointer (window, static_cast<void *>(&userdata));

	glfwMakeContextCurrent (window);
	gladLoadGLLoader ((void *(*)(const char *)) glfwGetProcAddress);

	glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback (window, key_callback);
	glfwSetCursorPosCallback (window, mouse_pos_callback);

	std::cerr << "OpenGL " << glGetString(GL_VERSION) << ", GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	glfwSwapInterval (1);

	GL (glEnable (GL_CULL_FACE));
	GL (glFrontFace (GL_CCW));
	GL (glClearColor (1, 1, 1, 1));
	GL (glEnable (GL_DEPTH_TEST));
	GL (glDepthFunc (GL_LESS));


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


	GLuint	program = new_shader_program (get_default_vertex_shader (), get_default_fragment_shader ());
	GL (glUseProgram (program));

	GLint	mvp_loc;
	mvp_loc = glGetUniformLocation (program, "MVP");

	glm::vec3	camera_forward(0, 0, 1), camera_position(0, 0, 2);
	float		movement_speed = 1.5f, rotation_speed = 0.5f;

	double last_frame_time = glfwGetTime ();
	double time;
	float delta;

	while (!glfwWindowShouldClose (window))
	{
		time = glfwGetTime ();
		delta = float (time - last_frame_time);
		last_frame_time = time;

		// Clip space
		int width, height;
		glfwGetFramebufferSize (window, &width, &height);
		GL (glViewport (0, 0, width, height));
		GL (glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		glm::mat4	projection = glm::infinitePerspective (glm::radians (60.f), (float) width / height, 0.1f);
		// Clip space END

		// Camera
		glm::vec3	camera_right = glm::normalize (glm::cross (glm::vec3 (0, 1, 0), camera_forward));
		glm::vec3	camera_forward_plane = glm::normalize (glm::cross (camera_right, glm::vec3 (0, 1, 0)));
		camera_position += camera_forward_plane * (-input.movement_delta.z * delta * movement_speed);
		camera_position += camera_right * (input.movement_delta.x * delta * movement_speed);
		camera_position.y += input.movement_delta.y * delta * movement_speed;

		camera_forward = glm::rotateY (camera_forward, -input.mouse_delta.x * delta * rotation_speed);
		camera_forward = glm::rotate (camera_forward, -input.mouse_delta.y * delta * rotation_speed, camera_right);
		camera_forward = glm::normalize (camera_forward);

		glm::mat4	camera = glm::lookAt (camera_position, camera_position - camera_forward, glm::vec3 (0, 1, 0));
		// Camera END

		// Model
		class MatrixStack {
			glm::mat4	matricies[8];
			size_t		matricies_count;

		public:
			MatrixStack (): matricies_count (0) {}
			glm::mat4	&push () {
				matricies[matricies_count] = glm::mat4 (1);
				matricies_count += 1;
				return (top ());
			}
			glm::mat4	&pop () {
				matricies_count -= 1;
				return (top ());
			}
			glm::mat4	&top () {
				return (matricies[matricies_count - 1]);
			}
			void		scale (const glm::vec3 &dim) {
				top () *= glm::scale (dim);
			}
			void		rotate (float angle, const glm::vec3 &axis) {
				top () *= glm::rotate (angle, axis);
			}
			void		translate (const glm::vec3 &delta) {
				top () *= glm::translate (delta);
			}
			glm::mat4	make () {
				size_t		index = 0;
				glm::mat4	result(1);

				while (index < matricies_count) {
					// result *= matricies[matricies_count - index - 1];
					result *= matricies[index];
					index += 1;
				}
				return (result);
			}
		};

		class MatrixStack	stack;

		auto draw = [&](class MatrixStack &stack) {
			glm::mat4	mvp = projection * camera * stack.make();

			glUniformMatrix4fv (mvp_loc, 1, GL_FALSE, glm::value_ptr(mvp));
			glDrawArrays (GL_TRIANGLES, 0, Array_Count (verticies_cube));
		};

		// -- Torso
		stack.push ();
		stack.scale (glm::vec3 (1.3f, 3.14f, 0.8f));
		draw (stack);
		// -- Torso END

		// -- Head
		stack.push ();
		stack.scale (glm::vec3 (1.f / 1.3f, 1 / 3.14f, 1 / 0.8f));
		stack.rotate (glm::radians (30.f), glm::vec3 (1, 0, 0));
		stack.scale (glm::vec3 (1.3f, 3.14f, 0.8f));
		stack.translate (glm::vec3 (0, 1, 0));
		draw (stack);
		// -- Head END

		// Model END

		memset (&input.mouse_delta, 0, sizeof input.mouse_delta);
		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	glfwTerminate ();
	return (0);
}


