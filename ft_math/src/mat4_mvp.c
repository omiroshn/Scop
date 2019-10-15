/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_mvp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:35:23 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/25 17:35:25 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

inline t_mat4	mat4_look_at(t_vec3 eye, t_vec3 target, t_vec3 up_dir)
{
	t_mat4			matrix;
	const t_vec3	forward = vec3_normalize(vec3_sub(eye, target));
	const t_vec3	left = vec3_normalize(vec3_cross(up_dir, forward));
	const t_vec3	up = vec3_cross(forward, left);

	matrix = mat4_identity();
	matrix.m11 = left.x;
	matrix.m21 = left.y;
	matrix.m31 = left.z;
	matrix.m12 = up.x;
	matrix.m22 = up.y;
	matrix.m32 = up.z;
	matrix.m13 = forward.x;
	matrix.m23 = forward.y;
	matrix.m33 = forward.z;
	matrix.m41 = -vec3_dot(left, eye);
	matrix.m42 = -vec3_dot(up, eye);
	matrix.m43 = -vec3_dot(forward, eye);
	return (matrix);
}

inline t_mat4	mat4_projection(float fov, float aspect, float near, float far)
{
	t_mat4	res;
	float	tan_half_angle;

	res = mat4_identity();
	tan_half_angle = TANF(fov / 2);
	res.m11 = 1.0f / (aspect * tan_half_angle);
	res.m22 = 1.0f / tan_half_angle;
	res.m33 = -(far + near) / (far - near);
	res.m34 = -1.0f;
	res.m43 = -(2.0f * far * near) / (far - near);
	return (res);
}

inline t_mat4	mat4_translate(t_mat4 mat, t_vec3 vec)
{
	t_mat4	res;

	res.m11 = mat.m11;
	res.m21 = mat.m21;
	res.m31 = mat.m31;
	res.m41 = mat.m41;
	res.m12 = mat.m12;
	res.m22 = mat.m22;
	res.m32 = mat.m32;
	res.m42 = mat.m42;
	res.m13 = mat.m13;
	res.m23 = mat.m23;
	res.m33 = mat.m33;
	res.m43 = mat.m43;
	res.m14 = mat.m14 + vec.x;
	res.m24 = mat.m24 + vec.y;
	res.m34 = mat.m34 + vec.z;
	res.m44 = mat.m44;
	return (res);
}

inline t_mat4	mat4_mul_mat4(t_mat4 m1, t_mat4 m2)
{
	t_mat4	res;
	t_vec4	r;
	int		col;
	int		i;

	col = -1;
	while (++col < 4)
	{
		i = 0;
		r = vec4_mult_scalar(m1.col[i], m2.col[col].v[i]);
		while (++i < 4)
			r = vec4_add(r, vec4_mult_scalar(m1.col[i], m2.col[col].v[i]));
		res.col[col] = r;
	}
	return (res);
}

inline t_mat4	mat4_rotate(t_mat4 mat, t_vec3 vec, float axis)
{
	t_mat4		res;
	const float	s = MSIN(axis);
	const float	one_c = 1.0f - MCOS(axis);
	const float	z = vec.z;
	const float	l = vec.x * vec.x + vec.y * vec.y + z * z;

	res.m11 = (vec.x * vec.x + (vec.y * vec.y + z * z) * MCOS(axis)) / l;
	res.m21 = (vec.x * vec.y * one_c + vec.z * MSQRT(l) * s) / l;
	res.m31 = (vec.x * z * one_c - vec.y * MSQRT(l) * s) / l;
	res.m41 = 0.0f;
	res.m12 = (vec.x * vec.y * one_c - vec.z * MSQRT(l) * s) / l;
	res.m22 = (vec.y * vec.y + (vec.x * vec.x + z * z) * MCOS(axis)) / l;
	res.m32 = (vec.y * z * one_c + vec.x * MSQRT(l) * s) / l;
	res.m42 = 0.0f;
	res.m13 = (vec.x * z * one_c + vec.y * MSQRT(l) * s) / l;
	res.m23 = (vec.y * z * one_c - vec.x * MSQRT(l) * s) / l;
	res.m33 = (z * z + (vec.x * vec.x + vec.y * vec.y) * MCOS(axis)) / l;
	res.m43 = 0.0f;
	res.m14 = 0.0f;
	res.m24 = 0.0f;
	res.m34 = 0.0f;
	res.m44 = 1.0f;
	res = mat4_mul_mat4(mat, res);
	return (res);
}
