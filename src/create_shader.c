/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_shader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:23:37 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/05 15:23:39 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		print_shader_compilation_info(const char *source, GLuint shader)
{
	GLsizei	size;
	GLchar	log[4096];

	glGetShaderInfoLog(shader, 4096, &size, log);
	ft_putendl("Shaders: Compilation stage:");
	ft_putendl(source);
	ft_putendl("Compilation log:");
	ft_putendl(log);
}

static GLuint	create_shader(const char *source, GLenum shader_type)
{
	GLint	err;
	GLuint	shader;

	shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, (const char *const *)&source, 0);
	glCompileShader(shader);
	err = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &err);
	if (err == GL_FALSE)
	{
		ft_putendl("Shader compilation failed");
		print_shader_compilation_info(source, shader);
		glDeleteShader(shader);
		return (0);
	}
	return (shader);
}

static GLuint	create_program(const char *vert, const char *frag)
{
	GLuint	vert_shader;
	GLuint	frag_shader;
	GLint	program_success;
	GLuint	program;

	if ((vert_shader = create_shader(vert, GL_VERTEX_SHADER)) == 0 ||
		(frag_shader = create_shader(frag, GL_FRAGMENT_SHADER)) == 0)
		put_error("Failed to read shaders.");
	program = glCreateProgram();
	glAttachShader(program, vert_shader);
	glAttachShader(program, frag_shader);
	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);
	glLinkProgram(program);
	program_success = GL_TRUE;
	glGetProgramiv(program, GL_LINK_STATUS, &program_success);
	if (program_success != GL_TRUE)
		print_link_error_info(program);
	glValidateProgram(program);
	return (program);
}

static int		check_shaders(int v_fd, int f_fd, size_t v_size, size_t f_size)
{
	char	*vertex_str;
	char	*fragment_str;
	int		program;

	vertex_str = (char*)malloc(v_size);
	if (read(v_fd, vertex_str, v_size) < 0)
		put_error("Failed to read shaders.");
	vertex_str[v_size] = '\0';
	fragment_str = (char*)malloc(f_size);
	if (read(f_fd, fragment_str, f_size) < 0)
		put_error("Failed to read shaders.");
	fragment_str[f_size] = '\0';
	program = create_program(vertex_str, fragment_str);
	free(vertex_str);
	free(fragment_str);
	return (program);
}

int				read_shaders(const char *vertex_path, const char *fragment_path)
{
	int			vertex_fd;
	int			fragment_fd;
	struct stat	st_v;
	struct stat	st_f;

	if ((vertex_fd = open(vertex_path, O_RDONLY)) < 0
		|| read(vertex_fd, NULL, 0) < 0)
		put_error("Failed to open vertex shader.");
	if ((fragment_fd = open(fragment_path, O_RDONLY)) < 0
		|| read(fragment_fd, NULL, 0) < 0)
		put_error("Failed to open fragment shader.");
	stat(vertex_path, &st_v);
	stat(fragment_path, &st_f);
	return (check_shaders(vertex_fd, fragment_fd, st_v.st_size, st_f.st_size));
}
