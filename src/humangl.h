#ifndef HUMANGL_H
#define HUMANGL_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class RenderObject;
class Node;

// SHADERS

const char	*get_default_vertex_shader (void);
const char	*get_default_fragment_shader (void);
GLuint	new_shader_program (const char *vertex_source, const char *fragment_source);

// INPUT

struct Input {
	glm::vec3	movement_delta;
	glm::vec2	mouse_position;
	glm::vec2	mouse_delta;
	int			node_selected;
};

struct WindowUserData {
	struct Input	*input;
};

void input_register_callbacks(GLFWwindow *window);

// GLFW INITIALIZATION

struct vertex {
	float	pos[3];
	float	color[4];
};

GLFWwindow		*initialize_glfw(WindowUserData&	userdata);
void			initialize_opengl(void);
RenderObject	*initialize_render_object(void);

// MVP

glm::mat4	calculate_projection(GLFWwindow *window);
glm::mat4	calculate_camera(Input *input, float delta);

// MODEL

Node	*create_human(const RenderObject *model);
void 	delete_human(Node *node);

// TIME

float get_delta();
float get_slider(float delta);

#endif //HUMANGL_H