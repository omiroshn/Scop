#include "scop.h"

void	put_error(const char *msg)
{
	system("leaks scop");
	if (!msg)
		exit(-1);
	ft_printf("Error: %s\n", msg);
	exit(-1);
}

void		print_link_error_info(GLuint program)
{
	GLsizei	size;
	GLchar	log[4096];

	ft_putendl("Shaders: Link stage failed.");
	glGetProgramInfoLog(program, 4096, &size, log);
	ft_putendl("Shaders: Program link log:");
	ft_putendl(log);
	put_error("Failed to read shaders. Program_success != GL_TRUE");
}