#include <vector>
#include <glad/glad.h>

#include "def.h"

extern GLenum error;

GLuint	new_shader_object (const char *source, GLenum kind) {
	GLuint	handle;
	GLint	success;

	GL (handle = glCreateShader (kind));
	GL (glShaderSource (handle, 1, &source, 0));
	GL (glCompileShader (handle));
	GL (glGetShaderiv (handle, GL_COMPILE_STATUS, &success));
	if (success == GL_FALSE) {
		char	message[32 * 1024];
		GLint	len;

		GL (glGetShaderInfoLog (handle, sizeof message - 1, &len, message));
		message[len] = 0;
		Debug ("Shader Compilation Error:\n%s", message);
		GL (glDeleteShader (handle));
		handle = 0;
	}
	return (handle);
}

const char	*get_default_vertex_shader (void) {
	return (
			"#version 410\n"

			"in vec3 v_pos;\n"
			"in vec4 v_color;\n"
			"out vec4 f_color;\n"
			"uniform mat4 MVP;\n"

			"void main () {\n"
			"f_color = v_color;\n"
			"gl_Position = MVP * vec4(v_pos, 1);\n"
			"}\n"
			);
}

const char	*get_default_fragment_shader (void) {
	return (
			"#version 410\n"

			"in vec4 f_color;\n"
			"out vec4 _color;\n"
			"uniform sampler2D u_tex;\n"

			"void main () {\n"
			"_color = f_color;\n"
			"}\n"
			);
}

GLuint	new_shader_program (const char *vertex_source, const char *fragment_source) {
	GLuint	program, vertex, fragment;

	program = 0;
	vertex = new_shader_object (vertex_source, GL_VERTEX_SHADER);
	if (vertex != 0) {
		fragment = new_shader_object (fragment_source, GL_FRAGMENT_SHADER);
		if (fragment != 0) {
			GLint	linked;

			GL (program = glCreateProgram ());
			GL (glAttachShader (program, vertex));
			GL (glAttachShader (program, fragment));
			GL (glLinkProgram (program));
			GL (glGetProgramiv (program, GL_LINK_STATUS, &linked));
			if (linked == GL_FALSE) {
				char	message[32 * 1024];
				GLint	len;

				GL (glGetProgramInfoLog (program, sizeof message - 1, &len, message));
				Debug ("Program Linkage Error:\n%s", message);
				GL (glDeleteProgram (program));
				program = 0;
			} else {
				GL (glDetachShader (program, vertex));
				GL (glDetachShader (program, fragment));
			}
			GL (glDeleteShader (fragment));
			fragment = 0;
		}
		GL (glDeleteShader (vertex));
		vertex = 0;
	}
	return (program);
}