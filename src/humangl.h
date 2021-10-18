#ifndef HUMANGL_H
#define HUMANGL_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <functional>

#include "Node.hpp"

// SHADERS

const char	*get_default_vertex_shader (void);
const char	*get_default_fragment_shader (void);
GLuint	new_shader_program (const char *vertex_source, const char *fragment_source);

// INPUT

struct Input {
	glm::vec3	movement_delta;
	glm::vec2	mouse_position;
	glm::vec2	mouse_delta;
};

struct WindowUserData {
	struct Input	*input;
};

void input_register_callbacks(GLFWwindow *window);

// GLFW INITIALIZATION

struct RenderObject {
	GLuint vbo;
	GLuint vao;
	GLuint program;
	GLchar *data;
	GLuint data_size;
};

GLFWwindow		*initialize_glfw(WindowUserData&	userdata);
void			initialize_opengl(void);
RenderObject	*initialize_buffers(void);

// MVP

glm::mat4	calculate_projection(GLFWwindow *window);
glm::mat4	calculate_camera(Input *input, float delta);

// MODEL

Node	*create_human(float slider);
//void draw_node(class MatrixStack &stack, const class Node &node);

#endif //HUMANGL_H