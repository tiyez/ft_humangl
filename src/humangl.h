#ifndef HUMANGL_H
#define HUMANGL_H

const char	*get_default_vertex_shader (void);
const char	*get_default_fragment_shader (void);
GLuint	new_shader_program (const char *vertex_source, const char *fragment_source);

#endif //HUMANGL_H
