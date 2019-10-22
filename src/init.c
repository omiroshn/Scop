/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:59:48 by omiroshn          #+#    #+#             */
/*   Updated: 2019/10/15 15:59:49 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		init_glew(SDL_Window *window)
{
	SDL_GLContext	context;
	GLenum			err;

	context = SDL_GL_CreateContext(window);
	glewExperimental = GL_TRUE;
	err = glewInit();
	if (err != GLEW_OK)
		put_error((const char *)glewGetErrorString(err));
	ft_printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

SDL_Window	*init_window(void)
{
	SDL_Window *window;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		put_error("Unable to initialize SDL.");
	window = SDL_CreateWindow("SCOP",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		960, 540, SDL_WINDOW_OPENGL);
	if (!window)
		put_error("Unable to create SDL window.");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
						SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetSwapInterval(1);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	return (window);
}

void		init_keys(short *key_states)
{
	int i;

	i = -1;
	while (++i < 255)
		key_states[i] = 0;
}

void		init_scop(t_scop *scop)
{
	scop->camera.position = vec3_init(0.0f, -4.0f, 15.0f);
	scop->camera.direction = vec3_init(0.0f, 0.0f, -1.0f);
	scop->camera.right = vec3_init(-1.0f, 0.0f, 0.0f);
	scop->camera.up = vec3_init(0.0f, -1.0f, 0.0f);
	scop->light.position = vec3_init(0.0f, -10.0f, 0.0f);
	scop->program_is_running = 1;
	scop->space_pressed = 1;
	scop->primitive_mode = 1;
	scop->mode = 1;
}
