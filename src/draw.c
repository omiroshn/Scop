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

void print_vec3(t_vec3 vec)
{
	printf("%.0f %.0f %.0f\n", vec.x, vec.y, vec.z);
}

void print_mat4(t_mat4 mat)
{
	printf("%f %f %f %f\n", mat.m11, mat.m12, mat.m13, mat.m14);
	printf("%f %f %f %f\n", mat.m21, mat.m22, mat.m23, mat.m24);
	printf("%f %f %f %f\n", mat.m31, mat.m32, mat.m33, mat.m34);
	printf("%f %f %f %f\n\n", mat.m41, mat.m42, mat.m43, mat.m44);
}

void	draw_skybox(t_scop *s, unsigned int size, unsigned int program)
{
	t_mat4 look_at;
	t_mat4 view;
	t_mat4 projection;

	look_at = mat4_look_at(s->camera.position,
		vec3_add(s->camera.position, s->camera.direction), s->camera.up);
	view = mat4_crop_mat3(look_at);
	projection = mat4_projection(TORAD(45.0f),
		1.0f * SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

	t_mat4 translate;
	t_mat4 rotate;

	translate = mat4_translate(s->model, s->camera.position)
	view = mat4_mul_mat4(translate, rotate);

	printf("look_at\n");
	print_mat4(look_at);
	printf("view\n");
	print_mat4(view);
	printf("projection\n");
	print_mat4(projection);

	exit(0);

	set_mat4(program, "projection", projection);
	set_mat4(program, "view", view);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, size);
	glDepthFunc(GL_LESS);
	glBindVertexArray(0);
}

void	draw_object(t_scop *s, unsigned int size, unsigned int program)
{
	t_mat4 view;
	t_mat4 projection;

	view = mat4_look_at(s->camera.position,
		vec3_add(s->camera.position, s->camera.direction), s->camera.up);
	projection = mat4_projection(TORAD(45.0f),
		1.0f * SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);
	if (!s->space_pressed)
		s->model = mat4_rotate(s->model,
			vec3_init(0.0f, 1.0f, 0.0f), s->timer.delta_time * TORAD(55.0f));
	set_mat4(program, "projection", projection);
	set_mat4(program, "view", view);
	set_mat4(program, "model", s->model);
	set_vec3(program, "lightPos", s->light.position);
	set_int1(program, "mode", s->mode);
	if (s->primitive_mode)
		glDrawArrays(GL_TRIANGLES, 0, size);
	else
		glDrawArrays(GL_LINES, 0, size);
	glBindVertexArray(0);
}
