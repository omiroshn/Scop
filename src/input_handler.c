/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:55:20 by omiroshn          #+#    #+#             */
/*   Updated: 2019/10/15 18:55:21 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	update_direction(t_scop *s)
{
	t_vec3 front;

	front.x = -cos(TORAD(0.0f)) * sin(TORAD(-s->camera.yaw));
	front.y = sin(TORAD(0.0f));
	front.z = -cos(TORAD(0.0f)) * cos(TORAD(-s->camera.yaw));
	s->camera.direction = vec3_normalize(front);
	s->camera.right = vec3_normalize(vec3_cross(s->camera.direction,
		vec3_init(0.0f, -1.0f, 0.0f)));
	s->camera.up = vec3_normalize(vec3_cross(s->camera.right,
		s->camera.direction));
}

static void	handle_keys(t_scop *s)
{
	const float camera_speed = s->timer.delta_time * 5.f;

	if (s->key_states[SDL_SCANCODE_W])
		s->camera.position = vec3_add(s->camera.position,
			vec3_mult_scalar(s->camera.direction, camera_speed));
	if (s->key_states[SDL_SCANCODE_S])
		s->camera.position = vec3_sub(s->camera.position,
			vec3_mult_scalar(s->camera.direction, camera_speed));
	if (s->key_states[SDL_SCANCODE_A])
		s->camera.position = vec3_sub(s->camera.position,
			vec3_mult_scalar(s->camera.right, camera_speed));
	if (s->key_states[SDL_SCANCODE_D])
		s->camera.position = vec3_add(s->camera.position,
			vec3_mult_scalar(s->camera.right, camera_speed));
	if (s->key_states[SDL_SCANCODE_Q])
		s->camera.position = vec3_sub(s->camera.position,
			vec3_mult_scalar(s->camera.up, camera_speed));
	if (s->key_states[SDL_SCANCODE_E])
		s->camera.position = vec3_add(s->camera.position,
			vec3_mult_scalar(s->camera.up, camera_speed));
	if (s->key_states[SDL_SCANCODE_LEFT])
		s->camera.yaw += 1.f;
	if (s->key_states[SDL_SCANCODE_RIGHT])
		s->camera.yaw -= 1.f;
}

static void	keydown(t_scop *s, SDL_Scancode scancode)
{
	s->key_states[scancode] = 1;
	if (scancode == SDL_SCANCODE_LEFTBRACKET)
		--s->mode < 1 ? s->mode = 6 : 0;
	if (scancode == SDL_SCANCODE_RIGHTBRACKET)
		++s->mode > 6 ? s->mode = 1 : 0;
	if (scancode == SDL_SCANCODE_SPACE)
		s->space_pressed ^= 1;
	if (scancode == SDL_SCANCODE_P)
		s->primitive_mode ^= 1;
}

void		handle_events(t_scop *s)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN
			&& e.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			s->program_is_running = 0;
		else if (e.type == SDL_KEYDOWN)
			keydown(s, e.key.keysym.scancode);
		else if (e.type == SDL_KEYUP)
			s->key_states[e.key.keysym.scancode] = 0;
		else if (e.type == SDL_MOUSEMOTION)
			if (e.motion.state & SDL_BUTTON_LMASK)
			{
				if (e.motion.xrel > 0)
					s->camera.yaw -= 1.0f;
				else if (e.motion.xrel < 0)
					s->camera.yaw += 1.0f;
			}
	}
	handle_keys(s);
	update_direction(s);
}
