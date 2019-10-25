/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 19:18:45 by omiroshn          #+#    #+#             */
/*   Updated: 2019/10/15 19:18:45 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	draw_skybox(t_scop *s, unsigned int size, unsigned int program)
{
	t_mat4 view;

	view = mat4_crop_mat3(mat4_look_at(s->camera.position,
		vec3_add(s->camera.position, s->camera.direction), s->camera.up));
	set_mat4(program, "projection", s->projection);
	set_mat4(program, "view", view);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, size);
	glDepthFunc(GL_LESS);
	glBindVertexArray(0);
}

void	draw_object(t_scop *s, unsigned int size, unsigned int program)
{
	t_mat4 view;

	view = mat4_look_at(s->camera.position,
		vec3_add(s->camera.position, s->camera.direction), s->camera.up);
	if (!s->space_pressed)
		s->model = mat4_rotate(s->model, vec3_init(0.0f, 1.0f, 0.0f),
			s->timer.delta_time * TORAD(55.0f));
	set_mat4(program, "projection", s->projection);
	set_mat4(program, "view", view);
	set_mat4(program, "model", s->model);
	set_vec3(program, "lightPos", s->light_pos);
	set_int1(program, "mode", s->mode);
	if (s->primitive_mode)
		glDrawArrays(GL_TRIANGLES, 0, size);
	else
		glDrawArrays(GL_LINES, 0, size);
	glBindVertexArray(0);
}
