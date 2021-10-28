#include <GLFW/glfw3.h>
#include "ftm.hpp"

float get_delta() {
	static double time;
	static double last_frame_time;
	float delta;

	if (time == 0 && last_frame_time == 0) {
		time = glfwGetTime();
		last_frame_time = glfwGetTime();
	}
	time = glfwGetTime ();
	delta = float (time - last_frame_time);
	last_frame_time = time;

	return delta;
}

float get_slider(float delta) {
	static const float	slider_speed = 1.f;
	static int			slider_direction = 1;
	static float		slider;

	slider += (float) slider_direction * slider_speed * delta;
	if (slider_direction > 0 && slider > 1) {
		slider_direction = -1;
	} else if (slider_direction < 0 && slider < 0) {
		slider_direction = 1;
	}
	return ftm::clamp (slider, 0.f, 1.f);
}