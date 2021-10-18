#ifndef HUMANGL_H
#define HUMANGL_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

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

GLFWwindow	*initialize_glfw(WindowUserData&	userdata);
void		initialize_opengl(void);
int			initialize_buffers(void);

#endif //HUMANGL_H