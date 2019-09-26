/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:20:59 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/05 15:21:00 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
#define SCOP_H

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "libft.h"
#include "get_next_line.h"
#include <stdint.h>
#include <mach/mach_time.h>

typedef	struct	s_timer
{
	uint64_t	start;
	uint64_t	current;
	uint64_t	current_time;
	uint64_t	numer;
	uint64_t	denom;
	float		ttime;
	float		old_time;
	float		delta_time;
}				t_timer;

#include "ft_math.h"

typedef struct	s_vertex
{
	t_vec4   position;
	t_vec3   normal;
	t_vec2   texCoords;
}				t_vertex;

typedef struct	s_binded
{
	unsigned int vao;
	unsigned int program;
}				t_binded;

typedef struct	s_camera
{
	t_vec3 position;
	t_vec3 direction;
	t_vec3 right;
	t_vec3 up;
}				t_camera;

typedef struct	s_light
{
	t_vec3 position;
}				t_light;

typedef	struct	s_scop
{
	short		key_states[256];
	t_timer		timer;
	t_camera	camera;
	t_light		light;
	t_mat4		model;
	// vertices
}				t_scop;


void			init_keys(short *key_states);
SDL_Window*		init_window();
void			init_glew(SDL_Window *window);
void			init_timer(t_timer *timer);
void			tick(t_timer *timer);

// #include "glm/glm.hpp"
// #include "glm/gtc/matrix_transform.hpp"
// #include "glm/gtc/quaternion.hpp"
// #include "glm/gtx/quaternion.hpp"
// #include <glm/gtx/euler_angles.hpp>

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
// #include <fstream>
// #include <sstream>
// #include <vector>
// #include <iostream>

#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)
#define get_offset(type, member) ((size_t)(&((type*)(1))->member)-1)

char		**ft_strsplit(char const *s, char c);
int			ft_array_length(char const *s, char c);
char		*ft_strtrim(char const *s);
void		free_strsplit(char **str);
int   read_shaders(const char *vertex_path, const char *fragment_path);

void draw_object(t_scop *s, unsigned int size, unsigned int program);
void draw_skybox(t_scop *s, unsigned int size, unsigned int program);

void set_mat4(unsigned int program, const char *name, t_mat4 matrix);
void set_vec3(unsigned int program, const char *name, t_vec3 vector);
void set_int1(unsigned int program, const char *name, int value);

#endif