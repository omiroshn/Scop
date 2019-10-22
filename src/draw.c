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

void print_quaternion(t_quaternion quat)
{
	printf("%f %f %f %f\n", quat.v.x, quat.v.y, quat.v.z, quat.w);
}

// look_at
// -0.220691 -0.951296 -0.215249 0
// -2.06782e-07 -0.220691 0.975344 0
// -0.975344 0.215249 0.0487042 0
// 14.6302 -4.1115 3.17081 1

// view
// -0.220691 -0.951296 -0.215249 0
// -2.06782e-07 -0.220691 0.975344 0
// -0.975344 0.215249 0.0487042 0
// 0 0 0 1

// projection
// 1.358 0 0 0
// 0 2.41421 0 0
// 0 0 -1.002 -1
// 0 0 -0.2002 0


// look_at
// -0.031856 -0.090393 -0.300655 0.000000
// 0.000000 -0.031856 0.948423 0.000000
// -0.095309 0.030213 0.100492 0.000000
// 1.429634 -0.580627 2.286305 1.000000

// view
// -0.031856 -0.090393 -0.300655 0.000000
// 0.000000 -0.031856 0.948423 0.000000
// -0.095309 0.030213 0.100492 0.000000
// 0.000000 0.000000 0.000000 1.000000

// projection
// 1.357995 0.000000 0.000000 0.000000
// 0.000000 2.414213 0.000000 0.000000
// 0.000000 0.000000 -1.002002 -1.000000
// 0.000000 0.000000 -0.200200 1.000000


// -0.173648 0.969846 0.17101 0
// 3.62021e-07 -0.173648 0.984808 0
// 0.984808 0.17101 0.0301533 0
// -14.7721 -3.25974 3.48693 1

// view
// -0.173648 0.969846 0.17101 0
// 3.62021e-07 -0.173648 0.984808 0
// 0.984808 0.17101 0.0301533 0
// 0 0 0 1

// projection
// 1.358 0 0 0
// 0 2.41421 0 0
// 0 0 -1.002 -1
// 0 0 -0.2002 0

// -0.005236 0.029244 0.171010 0.000000
// 0.000000 -0.005236 0.984807 0.000000
// 0.029696 0.005157 0.030153 0.000000
// -0.445433 -0.098293 3.486930 1.000000

// view
// -0.005236 0.029244 0.171010 0.000000
// 0.000000 -0.005236 0.984807 0.000000
// 0.029696 0.005157 0.030153 0.000000
// 0.000000 0.000000 0.000000 1.000000

// projection
// 1.357995 0.000000 0.000000 0.000000
// 0.000000 2.414213 0.000000 0.000000
// 0.000000 0.000000 -1.002002 -1.000000
// 0.000000 0.000000 -0.200200 1.000000

void	draw_skybox(t_scop *s, unsigned int size, unsigned int program)
{
	// t_vec3 up = vec3_init(s->camera.up.x, s->camera.up.y, s->camera.up.z);
	// t_vec3 right = vec3_init(s->camera.right.x, s->camera.right.y, s->camera.right.z);
	// t_quaternion q = init_quat(up, 2  * 50);
	// t_quaternion r = init_quat(right, 2  * 50);
	// t_quaternion su = quat_mult_quat(q,r);
	
	// t_vec3 dir = vec3_init(s->camera.direction.x, s->camera.direction.y, s->camera.direction.z);
	// dir = quat_transform_vec3(su, dir);
	// s->camera.direction.x = dir.x;
	// s->camera.direction.y = dir.y;
	// s->camera.direction.z = dir.z;
	
	// right = vec3_cross(dir, up);
	// s->camera.right.x = right.x;
	// s->camera.right.y = right.y;
	// s->camera.right.z = right.z;

	// up = vec3_cross(right, dir);
	// s->camera.up.x = up.x;
	// s->camera.up.y = up.y;
	// s->camera.up.z = up.z;



	t_mat4 look_at;
	t_mat4 view;
	t_mat4 projection;

	look_at = mat4_look_at(s->camera.position,
		vec3_add(s->camera.position, s->camera.direction), s->camera.up);
	view = mat4_crop_mat3(look_at);
	projection = mat4_projection(TORAD(45.0f),
		1.0f * SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

	printf("look_at\n");
	print_mat4(look_at);
	printf("view\n");
	print_mat4(view);
	// projection.m44 = 0.0f;
	printf("projection\n");
	print_mat4(projection);

	// exit(0);


	// t_mat4 rotate;
	// t_mat4 view;

	// rotate = mat4_euler_angle_xyz(s->camera.yaw,
	// 	s->camera.pitch, s->camera.roll);
	// view = mat4_crop_mat3(mat4_mul_mat4(rotate, s->skybox_translate));
	set_mat4(program, "view", view);
	set_mat4(program, "projection", projection);
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


// <<<<<<< HEAD
// 	view = mat4_look_at(s->camera.position,
// 		vec3_add(s->camera.position, s->camera.direction), s->camera.up);
// 	projection = mat4_projection(TORAD(45.0f),
// 		1.0f * SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);

// =======
// 	translate = mat4_translate(s->camera.position);
// 	// print_mat4(translate);
// 	rotate = mat4_euler_angle_xyz(s->camera.yaw, s->camera.pitch, s->camera.roll);
// 	// print_mat4(rotate);
// 	view = mat4_mul_mat4(translate, rotate);
// 	view.m11 = -view.m11;
// 	view.m22 = -view.m22;
// 	view.m43 = -view.m43;
// 	print_mat4(view);
// 	// view = mat4_look_at(s->camera.position,
// 	// 	vec3_add(s->camera.position, s->camera.direction), s->camera.up);

// 	// print_mat4(view);
// 	// exit(0);
// >>>>>>> 3fbbf9907a7e71582db11103f1c17a046833ed43
	// if (!s->space_pressed)
	// {
	// 	s->model = mat4_rotate(s->model,
	// 		vec3_init(0.0f, 1.0f, 0.0f), s->timer.delta_time * TORAD(55.0f));
	// }
	set_mat4(program, "model", s->model);
	set_mat4(program, "view", view);
	set_mat4(program, "projection", projection);
	set_vec3(program, "lightPos", s->light.position);
	set_int1(program, "mode", s->mode);
	if (s->primitive_mode)
		glDrawArrays(GL_TRIANGLES, 0, size);
	else
		glDrawArrays(GL_LINES, 0, size);
	glBindVertexArray(0);
}
