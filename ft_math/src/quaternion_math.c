/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_math.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:41:47 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/26 16:41:47 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include <pmmintrin.h>

inline t_quaternion		invert_quat(t_quaternion q)
{
	q = vec4_mult_scalar(q, -1.0f);
	q.w *= -1.0f;
	return (q);
}

inline t_quaternion		quat_mult_quat(t_quaternion xyzw, t_quaternion abcd)
{
	__m128 vec[6];

	vec[0] = _mm_shuffle_ps(xyzw.m128, xyzw.m128, _MM_SHUFFLE(0, 1, 2, 3));
	vec[1] = _mm_shuffle_ps(abcd.m128, abcd.m128, _MM_SHUFFLE(0, 1, 0, 1));
	vec[2] = _mm_shuffle_ps(abcd.m128, abcd.m128, _MM_SHUFFLE(2, 3, 2, 3));
	vec[3] = _mm_hsub_ps(_mm_mul_ps(xyzw.m128, vec[1]),
								_mm_mul_ps(vec[0], vec[2]));
	vec[4] = _mm_hadd_ps(_mm_mul_ps(xyzw.m128, vec[2]),
								_mm_mul_ps(vec[0], vec[1]));
	vec[5] = _mm_addsub_ps(
					_mm_shuffle_ps(vec[4], vec[3], _MM_SHUFFLE(3, 2, 1, 0)),
					_mm_shuffle_ps(vec[3], vec[4], _MM_SHUFFLE(2, 3, 0, 1)));
	return (vec4_init_m128(
		_mm_shuffle_ps(vec[5], vec[5], _MM_SHUFFLE(2, 1, 3, 0))));
}

inline t_quaternion		quat_mult_vec3(t_quaternion q, t_vec3 v)
{
	t_quaternion	res;

	res.x = q.y * v.z - q.z * v.y;
	res.y = q.z * v.x - q.x * v.z;
	res.z = q.x * v.y - q.y * v.x;
	res = vec3_add(vec3_mult_scalar(v, q.w), res);
	res.w = -1.0f * vec3_dot(q, v);
	return (res);
}

inline t_vec3			quat_transform_vec3(t_quaternion q, t_vec3 v)
{
	return (vec3_normalize(quat_mult_quat(
								quat_mult_vec3(q, v),
								invert_quat(q))));
}
