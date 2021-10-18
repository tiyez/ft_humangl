#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "def.h"
#include "humangl.h"

#include "Node.hpp"
#include "MatrixStack.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

extern GLenum error;

int main () {
	Input			input;
	WindowUserData	userdata = { &input };
	GLFWwindow *window = initialize_glfw(userdata);
	input_register_callbacks(window);
	initialize_opengl();

//	RenderObject *cube = initialize_buffers(); // TODO: just moving code into this function destroys render ?!

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

	double last_frame_time = glfwGetTime ();
	double time;
	float delta;

	float slider = 0, slider_speed = 1.f;
	int slider_direction = 1;

	while (!glfwWindowShouldClose (window))
	{
		time = glfwGetTime ();
		delta = float (time - last_frame_time);
		last_frame_time = time;

		slider += slider_direction * slider_speed * delta;
		if (slider_direction > 0 & slider > 1) {
			slider_direction = -1;
		} else if (slider_direction < 0 && slider < 0) {
			slider_direction = 1;
		}
		slider = glm::clamp (slider, 0.f, 1.f);

		glm::mat4 projection = calculate_projection(window);
		glm::mat4 camera = calculate_camera(userdata.input, delta);

		// Model
		class MatrixStack	stack;

		auto draw = [&](const glm::mat4 &model) {
			glm::mat4	mvp = projection * camera * model;

			glUniformMatrix4fv (mvp_loc, 1, GL_FALSE, glm::value_ptr(mvp));
			glDrawArrays (GL_TRIANGLES, 0, Array_Count (verticies_cube));
		};

		std::function<void (class MatrixStack &stack, const class Node &node)> draw_node = [&](class MatrixStack &stack, const class Node &node) {
			stack.push ();
				if (node.parent) {
					stack.translate ((node.parent->scale / 2.f) * node.parent_origin);
				}
				if (node.rotation_angle != 0) { // TODO(viktor): epsilon
					stack.rotate (node.rotation_angle, node.rotation_axis);
				}
				stack.translate (-((node.scale / 2.f) * node.self_origin));
				stack.push ();
					stack.scale (node.scale);
					draw (stack.top ());
				stack.pop ();
				for (auto &child : node.childs) {
					draw_node (stack, *child);
				}
			stack.pop ();
		};

		Node *human = create_human(slider);

		// Draw
		draw_node (stack, *human);
		// Model END

		memset (&input.mouse_delta, 0, sizeof input.mouse_delta);
		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	glfwTerminate ();
	return (0);
}


