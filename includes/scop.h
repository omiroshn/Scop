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
# define SCOP_H

# include <GL/glew.h>
# include <SDL2/SDL.h>

# include "libft.h"
# include "ft_math.h"
# include "get_next_line.h"

# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

# include <stdint.h>
# include <mach/mach_time.h>

# define get_offset(type, member) ((size_t)(&((type*)(1))->member)-1)

# define SCREEN_WIDTH 960.f
# define SCREEN_HEIGHT 540.f
# define KOEF(x) (x + 1.2f) / 2.4f

typedef struct		s_binded
{
	unsigned int	vao;
	unsigned int	program;
}					t_binded;

typedef struct		s_vertex
{
	t_vec4			position;
	t_vec3			normal;
	t_vec2			tex_coords;
}					t_vertex;

typedef struct		s_tmp_vertex
{
	t_vec4			*vertex;
	t_vec2			*uv;
	t_vec3			*normal;
	GLushort		*vertex_indices;
	GLushort		*uv_indices;
	GLushort		*normal_indices;
	int				vertex_count;
	int				texture_count;
	int				normal_count;
	int				faces_count;
}					t_tmp_vertex;

typedef struct		s_light
{
	t_vec3			position;
}					t_light;

typedef struct		s_camera
{
	t_vec3			position;
	t_vec3			direction;
	t_vec3			right;
	t_vec3			up;
}					t_camera;

typedef	struct		s_timer
{
	uint64_t		start;
	uint64_t		current;
	uint64_t		current_time;
	uint64_t		numer;
	uint64_t		denom;
	float			ttime;
	float			old_time;
	float			delta_time;
}					t_timer;

typedef	struct		s_scop
{
	t_timer			timer;
	t_camera		camera;
	t_light			light;
	t_mat4			model;
	short			key_states[256];
	short			program_is_running;
	short			space_pressed;
	short			primitive_mode;
	short			mode;
	int				obj_size;
	int				skybox_size;
	unsigned int	objectTextureID;
	unsigned int	skyboxTextureID;
	t_binded		bindedObj;
	t_binded		cubemapObj;
}					t_scop;

/*
** bind_obj.c
*/
unsigned int		bind_cubemap();
unsigned int		bind_texture(char *path);
t_binded			set_up_object(t_vertex *vertices, int size);
t_binded			set_up_skybox(t_vertex *vertices, int size);

/*
** parse_obj.c
*/
void				parse(t_tmp_vertex *v, char *line, int index);
int					get_faces(char *line);
int					get_size_of_obj(char *filename);

/*
** helpers.c
*/
void				free_strsplit(char **str);
int					get_size(char **sub);

/*
** cut_string.c
*/
void				cut_face_string(t_tmp_vertex *v, char *line, int *faces_count);
t_vec3				cut_normal_string(char *line);
t_vec2				cut_texture_string(char *line);
t_vec4				cut_vertex_string(char *line);


/*
** load_obj.c
*/
t_binded			load_obj(t_timer *timer, char *filename, int size, short skybox);
void				fill_vertex_array(t_vertex *vertices, t_tmp_vertex v, int size);
void				free_tmp_struct(t_tmp_vertex *v);
void				init_temp_struct(t_tmp_vertex *v, int size);

/*
** draw.c
*/
void				draw_object(t_scop *s, unsigned int size, unsigned int program);
void				draw_skybox(t_scop *s, unsigned int size, unsigned int program);

/*
** init.c
*/
void				init_keys(short *key_states);
SDL_Window*			init_window();
void				init_glew(SDL_Window *window);
void				init_scop(t_scop *scop);

/*
** timer.c
*/
void				update_time(t_timer *timer);
void				init_timer(t_timer *timer);
float				time_elapsed(t_timer *timer);

/*
** timer.c
*/
void				put_error(const char *msg);
void				print_link_error_info(GLuint program);

/*
** create_shader.c
*/
int   				read_shaders(const char *vertex_path, const char *fragment_path);

/*
** shader_locations.c
*/
void				set_mat4(unsigned int program, const char *name, t_mat4 matrix);
void				set_vec3(unsigned int program, const char *name, t_vec3 vector);
void				set_int1(unsigned int program, const char *name, int value);

#endif