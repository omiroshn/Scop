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
	t_mat4 rotate;
	t_mat4 view;

	rotate = mat4_euler_angle_xyz(s->camera.yaw,
		s->camera.pitch, s->camera.roll);
	view = mat4_crop_mat3(mat4_mul_mat4(rotate, s->skybox_translate));
	set_mat4(program, "projection", s->projection);
	set_mat4(program, "view", view);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, size);
	glDepthFunc(GL_LESS);
	glBindVertexArray(0);
}

void	draw_object(t_scop *s, unsigned int size, unsigned int program)
{
	t_mat4 translate;
	t_mat4 rotate;
	t_mat4 view;

	translate = mat4_translate(s->camera.position);
	// print_mat4(translate);
	rotate = mat4_euler_angle_xyz(s->camera.yaw, s->camera.pitch, s->camera.roll);
	// print_mat4(rotate);
	view = mat4_mul_mat4(translate, rotate);
	view.m11 = -view.m11;
	view.m22 = -view.m22;
	view.m43 = -view.m43;
	print_mat4(view);
	// view = mat4_look_at(s->camera.position,
	// 	vec3_add(s->camera.position, s->camera.direction), s->camera.up);

	// print_mat4(view);
	// exit(0);
	if (!s->space_pressed)
	{
		s->model = mat4_rotate(s->model,
			vec3_init(0.0f, 1.0f, 0.0f), s->timer.delta_time * TORAD(55.0f));
	}
	set_mat4(program, "model", s->model);
	set_mat4(program, "view", view);
	set_mat4(program, "projection", s->projection);
	set_vec3(program, "lightPos", s->light.position);
	set_int1(program, "mode", s->mode);
	if (s->primitive_mode)
		glDrawArrays(GL_TRIANGLES, 0, size);
	else
		glDrawArrays(GL_LINES, 0, size);
	glBindVertexArray(0);
}
