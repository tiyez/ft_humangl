#include <GLFW/glfw3.h>

#include "humangl.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	WindowUserData	*userdata = static_cast<WindowUserData *>(glfwGetWindowUserPointer (window));
	Input			*input = userdata->input;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (action == GLFW_PRESS) {
		switch (key) {
			// Movement
			case GLFW_KEY_D: { input->movement_delta.x += 1; } break ;
			case GLFW_KEY_A: { input->movement_delta.x += -1; } break ;
			case GLFW_KEY_W: { input->movement_delta.z += 1; } break ;
			case GLFW_KEY_S: { input->movement_delta.z += -1; } break ;
			case GLFW_KEY_E: { input->movement_delta.y += 1; } break ;
			case GLFW_KEY_Q: { input->movement_delta.y += -1; } break ;
			// Scale Resize	TODO: make scale resize by shift key??
			case GLFW_KEY_T: { input->scale_delta.x +=  0.03; } break ;
			case GLFW_KEY_G: { input->scale_delta.x += -0.03; } break ;
			case GLFW_KEY_Y: { input->scale_delta.z +=  0.03; } break ;
			case GLFW_KEY_H: { input->scale_delta.z += -0.03; } break ;
			case GLFW_KEY_U: { input->scale_delta.y +=  0.03; } break ;
			case GLFW_KEY_J: { input->scale_delta.y += -0.03; } break ;
		}
	} else if (action == GLFW_RELEASE) {
		switch (key) {
			// Movement
			case GLFW_KEY_D: { input->movement_delta.x -= 1; } break ;
			case GLFW_KEY_A: { input->movement_delta.x -= -1; } break ;
			case GLFW_KEY_W: { input->movement_delta.z -= 1; } break ;
			case GLFW_KEY_S: { input->movement_delta.z -= -1; } break ;
			case GLFW_KEY_E: { input->movement_delta.y -= 1; } break ;
			case GLFW_KEY_Q: { input->movement_delta.y -= -1; } break ;
			// Scale Resize	TODO: make scale resize by shift key??
			case GLFW_KEY_T: { input->scale_delta.x -=  0.03; } break ;
			case GLFW_KEY_G: { input->scale_delta.x -= -0.03; } break ;
			case GLFW_KEY_Y: { input->scale_delta.z -=  0.03; } break ;
			case GLFW_KEY_H: { input->scale_delta.z -= -0.03; } break ;
			case GLFW_KEY_U: { input->scale_delta.y -=  0.03; } break ;
			case GLFW_KEY_J: { input->scale_delta.y -= -0.03; } break ;
			// Select Node
			case GLFW_KEY_N: { input->node_selected++; } break;
			case GLFW_KEY_B: { input->node_selected--; } break;
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

void input_register_callbacks(GLFWwindow *window) {
	glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback (window, key_callback);
	glfwSetCursorPosCallback (window, mouse_pos_callback);
}