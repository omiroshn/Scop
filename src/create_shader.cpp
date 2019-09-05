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
#include "debug.h"

static void		print_shader_compilation_info(const char *source, GLuint shader)
{
	GLsizei	size;
	GLchar	log[4096];

	glGetShaderInfoLog(shader, 4096, &size, log);
	printf("Shader %s\ncompilation log:\n %s\n", source, log);
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
		printf("Shader compilation failed.\n");
		print_shader_compilation_info(source, shader);
		glDeleteShader(shader);
		return (0);
	}
	return (shader);
}

static void		print_link_info(GLuint program)
{
	GLsizei	size;
	GLchar	log[4096];

	printf("Shaders: Link stage failed.\n");
	glGetProgramInfoLog(program, 4096, &size, log);
	printf("Shaders: Program link log:\n %s\n", log);
}

GLuint			create_program(const char *vert, const char *frag)
{
	GLuint	vert_shader;
	GLuint	frag_shader;
	GLint	programSuccess;
	GLuint	program;

	if ((vert_shader = create_shader(vert, GL_VERTEX_SHADER)) == 0 ||
		(frag_shader = create_shader(frag, GL_FRAGMENT_SHADER)) == 0)
		return (0);
	program = glCreateProgram();
	glAttachShader(program, vert_shader);
	glAttachShader(program, frag_shader);

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	glLinkProgram(program);
	programSuccess = GL_TRUE;
	glGetProgramiv(program, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
		print_link_info(program);
		return (0);
	}
	GLCall( glValidateProgram(program) );
	return (program);
}


int   read_shaders(const char *vertex_path, const char *fragment_path)
{
	char    *vertex_str = NULL;
	char    *fragment_str = NULL;
	struct  stat st;
	int     v_size;
	int     f_size;
	
	const int vertex_fd = open(vertex_path, O_RDONLY);
	const int fragment_fd = open(fragment_path, O_RDONLY);
	
	stat(vertex_path, &st);
	v_size = st.st_size;
	stat(fragment_path, &st);
	f_size = st.st_size;
	
	vertex_str = (char*)malloc(v_size);
	if (read(vertex_fd, vertex_str, v_size) < 0) {
		perror("Shaders: Error in reading.\n");
		return (0);
	}
	vertex_str[v_size] = '\0';
	
	fragment_str = (char*)malloc(f_size);
	if (read(fragment_fd, fragment_str, f_size) < 0) {
		perror("Shaders: Error in reading.\n");
		return (0);
	}
	fragment_str[f_size] = '\0';
	
	int program;
	program = create_program(vertex_str, fragment_str);
	if (!program)
	{
		printf("Shaders: Failed to read shaders.\n");
		return (0);
	}
	free(vertex_str);
	free(fragment_str);
	return (program);
}
