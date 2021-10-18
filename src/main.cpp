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

	RenderObject *cube = initialize_render_object();
//	struct vertex vertices[36];					// TODO: Stack memory fucked up ??? (if remove this render fucks up)
	float stack_fail[36 * sizeof (float) * 7];	// TODO: Stack memory fucked up ??? (if remove this render fucks up)

	while (!glfwWindowShouldClose (window))
	{
		float delta = get_delta();
		float slider = get_slider(delta);

		glm::mat4 projection = calculate_projection(window);
		glm::mat4 camera = calculate_camera(userdata.input, delta);

		// Model
		class MatrixStack	stack;

		auto draw = [&](const glm::mat4 &model) {
			glm::mat4	mvp = projection * camera * model;

			glUniformMatrix4fv (cube->mvp_loc, 1, GL_FALSE, glm::value_ptr(mvp));
			glDrawArrays (GL_TRIANGLES, 0, cube->verts_count);
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


