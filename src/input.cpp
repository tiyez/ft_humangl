#include <GLFW/glfw3.h>

#include "humangl.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	WindowUserData	*userdata = static_cast<WindowUserData *>(glfwGetWindowUserPointer (window));
	Input			*input = userdata->input;
	float			shift = (mods & GLFW_MOD_SHIFT) ? -1 : 1;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		// glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (action == GLFW_PRESS) {
		switch (key) {
			// Movement
			case GLFW_KEY_D: { input->movement_delta.x +=  1; } break ;
			case GLFW_KEY_A: { input->movement_delta.x += -1; } break ;
			case GLFW_KEY_W: { input->movement_delta.z +=  1; } break ;
			case GLFW_KEY_S: { input->movement_delta.z += -1; } break ;
			case GLFW_KEY_E: { input->movement_delta.y +=  1; } break ;
			case GLFW_KEY_Q: { input->movement_delta.y += -1; } break ;
			// Scale
			case GLFW_KEY_1: { input->scale_delta.x +=  0.03f * shift; } break ;
			case GLFW_KEY_2: { input->scale_delta.y +=  0.03f * shift; } break ;
			case GLFW_KEY_3: { input->scale_delta.z +=  0.03f * shift; } break ;
			// Color
			case GLFW_KEY_4: { input->color_delta.x +=  0.03f * shift; } break ;
			case GLFW_KEY_5: { input->color_delta.y +=  0.03f * shift; } break ;
			case GLFW_KEY_6: { input->color_delta.z +=  0.03f * shift; } break ;
			// Rotate
			case GLFW_KEY_7: { input->rotate_euler.x += glm::radians (0.5f * shift); } break ;
			case GLFW_KEY_8: { input->rotate_euler.y += glm::radians (0.5f * shift); } break ;
			case GLFW_KEY_9: { input->rotate_euler.z += glm::radians (0.5f * shift); } break ;
			// Start/Stop animation
			case GLFW_KEY_SPACE: { input->animate = !input->animate; } break;
			// Print Node
			case GLFW_KEY_P: {input->print_selected = true;} break;
			// Console
			case GLFW_KEY_C: { input->console = true; } break ;
			// Select
			case GLFW_KEY_N: { (shift > 0 ? input->select_node : input->select_frame) += 1; } break;
			case GLFW_KEY_B: { (shift > 0 ? input->select_node : input->select_frame) += -1; } break;
			// Origin
			case GLFW_KEY_RIGHT: { input->origin_delta.x +=  1; } break ;
			case GLFW_KEY_LEFT: { input->origin_delta.x += -1; } break ;
			case GLFW_KEY_UP: { (shift > 0 ? input->origin_delta.z : input->origin_delta.y) +=  1; } break ;
			case GLFW_KEY_DOWN: { (shift > 0 ? input->origin_delta.z : input->origin_delta.y) += -1; } break ;
			// is_parent_origin
			case GLFW_KEY_X: { input->is_parent_origin = !input->is_parent_origin; }  break ;
			// Rotation_translation index change
			case GLFW_KEY_Z: { input->is_rotation_frame = !input->is_rotation_frame; }  break ;
		}
	} else if (action == GLFW_RELEASE) {
		switch (key) {
			// Movement
			case GLFW_KEY_D: { input->movement_delta.x -=  1; } break ;
			case GLFW_KEY_A: { input->movement_delta.x -= -1; } break ;
			case GLFW_KEY_W: { input->movement_delta.z -=  1; } break ;
			case GLFW_KEY_S: { input->movement_delta.z -= -1; } break ;
			case GLFW_KEY_E: { input->movement_delta.y -=  1; } break ;
			case GLFW_KEY_Q: { input->movement_delta.y -= -1; } break ;
			// Scale
			case GLFW_KEY_1: { input->scale_delta.x -=  0.03f * shift; } break ;
			case GLFW_KEY_2: { input->scale_delta.y -=  0.03f * shift; } break ;
			case GLFW_KEY_3: { input->scale_delta.z -=  0.03f * shift; } break ;
			// Color
			case GLFW_KEY_4: { input->color_delta.x -=  0.03f * shift; } break ;
			case GLFW_KEY_5: { input->color_delta.y -=  0.03f * shift; } break ;
			case GLFW_KEY_6: { input->color_delta.z -=  0.03f * shift; } break ;
			// Rotate
			case GLFW_KEY_7: { input->rotate_euler.x -= glm::radians (0.5f * shift); } break ;
			case GLFW_KEY_8: { input->rotate_euler.y -= glm::radians (0.5f * shift); } break ;
			case GLFW_KEY_9: { input->rotate_euler.z -= glm::radians (0.5f * shift); } break ;
			// Origin
			case GLFW_KEY_RIGHT: { input->origin_delta.x -=  1; } break ;
			case GLFW_KEY_LEFT: { input->origin_delta.x -= -1; } break ;
			case GLFW_KEY_UP: { (shift > 0 ? input->origin_delta.z : input->origin_delta.y) -=  1; } break ;
			case GLFW_KEY_DOWN: { (shift > 0 ? input->origin_delta.z : input->origin_delta.y) -= -1; } break ;
		}
	}
}

static bool g_is_mouse_pushed = false;

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		g_is_mouse_pushed = true;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		g_is_mouse_pushed = false;
	}
}

static void	mouse_pos_callback (GLFWwindow *window, double x, double y) {
	WindowUserData	*userdata = static_cast<WindowUserData *>(glfwGetWindowUserPointer (window));
	Input			*input = userdata->input;

	if (!g_is_mouse_pushed) {
		input->mouse_position.x = x;
		input->mouse_position.y = y;
		return ;
	}

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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetKeyCallback (window, key_callback);
	glfwSetCursorPosCallback (window, mouse_pos_callback);
	glfwSetMouseButtonCallback (window, mouse_button_callback);
}