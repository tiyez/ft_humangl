#include <GLFW/glfw3.h>

#include "humangl.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	WindowUserData	*userdata = static_cast<WindowUserData *>(glfwGetWindowUserPointer (window));
	Input			*input = userdata->input;
	float			shift = mods && GLFW_MOD_SHIFT ? -1 : 1;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (action == GLFW_PRESS) {
		switch (key) {
			// Movement
			case GLFW_KEY_D: { input->movement_delta.x +=  2; } break ;
			case GLFW_KEY_A: { input->movement_delta.x += -2; } break ;
			case GLFW_KEY_W: { input->movement_delta.z +=  2; } break ;
			case GLFW_KEY_S: { input->movement_delta.z += -2; } break ;
			case GLFW_KEY_E: { input->movement_delta.y +=  2; } break ;
			case GLFW_KEY_Q: { input->movement_delta.y += -2; } break ;
			// Scale
			case GLFW_KEY_1: { input->scale_delta.x +=  0.03f * shift; } break ;
			case GLFW_KEY_2: { input->scale_delta.y +=  0.03f * shift; } break ;
			case GLFW_KEY_3: { input->scale_delta.z +=  0.03f * shift; } break ;
			// Color
			case GLFW_KEY_4: { input->color_delta.x +=  0.03f * shift; } break ;
			case GLFW_KEY_5: { input->color_delta.y +=  0.03f * shift; } break ;
			case GLFW_KEY_6: { input->color_delta.z +=  0.03f * shift; } break ;
			// Start/Stop animation
			case GLFW_KEY_SPACE: { input->animate = !input->animate; } break;
			// Print Node
			case GLFW_KEY_P: {input->print_selected = true;} break;
		}
	} else if (action == GLFW_RELEASE) {
		switch (key) {
			// Movement
			case GLFW_KEY_D: { input->movement_delta.x -=  2; } break ;
			case GLFW_KEY_A: { input->movement_delta.x -= -2; } break ;
			case GLFW_KEY_W: { input->movement_delta.z -=  2; } break ;
			case GLFW_KEY_S: { input->movement_delta.z -= -2; } break ;
			case GLFW_KEY_E: { input->movement_delta.y -=  2; } break ;
			case GLFW_KEY_Q: { input->movement_delta.y -= -2; } break ;
			// Scale
			case GLFW_KEY_1: { input->scale_delta.x -=  0.03f * shift; } break ;
			case GLFW_KEY_2: { input->scale_delta.y -=  0.03f * shift; } break ;
			case GLFW_KEY_3: { input->scale_delta.z -=  0.03f * shift; } break ;
			// Color
			case GLFW_KEY_4: { input->color_delta.x -=  0.03f * shift; } break ;
			case GLFW_KEY_5: { input->color_delta.y -=  0.03f * shift; } break ;
			case GLFW_KEY_6: { input->color_delta.z -=  0.03f * shift; } break ;
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