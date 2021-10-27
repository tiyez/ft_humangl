#ifndef HUMANGL_H
#define HUMANGL_H

#include <glm/glm.hpp>
#include "ftm.hpp"
#include <GLFW/glfw3.h>

class RenderObject;
class Node;
struct NodeData;

// SHADERS

const char	*get_default_vertex_shader (void);
const char	*get_default_fragment_shader (void);
GLuint	new_shader_program (const char *vertex_source, const char *fragment_source);

// INPUT

struct Input {
	glm::vec3	movement_delta;
	glm::vec2	mouse_position;
	glm::vec2	mouse_delta;
	glm::vec3	translate;
	int			select_node;
	int			select_frame;
	glm::vec3	scale_delta;
	glm::vec3	color_delta;
	bool		print_selected;
	bool		animate;
	glm::vec3	rotate_euler;
	bool		console;
	glm::vec3	origin_delta;
	bool		is_parent_origin;
	bool		is_rotation_frame;
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

ftm::mat4	calculate_projection(GLFWwindow *window);
glm::mat4	calculate_camera(Input *input, float delta);

// TIME

float get_delta();
float get_slider(float delta);

#endif //HUMANGL_H