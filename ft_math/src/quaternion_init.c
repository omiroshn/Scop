/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:41:39 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/26 16:41:39 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

t_quaternion	invert_quat(t_quaternion q)
{
	t_quaternion	res;

	res.w = q.w;
	res.v = vec3_mult_scalar(q.v, -1);
	return (res);
}

t_quaternion	quat_mult_quat(t_quaternion q1, t_quaternion q2)
{
	t_quaternion	res;

	res.w = q1.w * q2.w - q1.v.x * q2.v.x - q1.v.y * q2.v.y - q1.v.z * q2.v.z;
	res.v.x = q1.w * q2.v.x + q1.v.x * q2.w + q1.v.y * q2.v.z - q1.v.z * q2.v.y;
	res.v.y = q1.w * q2.v.y - q1.v.x * q2.v.z + q1.v.y * q2.w + q1.v.z * q2.v.x;
	res.v.z = q1.w * q2.v.z + q1.v.x * q2.v.y - q1.v.y * q2.v.x + q1.v.z * q2.w;
	return (res);
}

t_quaternion	quat_mult_3(t_quaternion q, t_vec3 v)
{
	t_quaternion	res;

	res.w = -q.v.x * v.x - q.v.y * v.y - q.v.z * v.z;
	res.v.x = q.w * v.x + q.v.y * v.z - q.v.z * v.y;
	res.v.y = q.w * v.y - q.v.x * v.z + q.v.z * v.x;
	res.v.z = q.w * v.z + q.v.x * v.y - q.v.y * v.x;
	return (res);
}

t_vec3			quat_transform_vec3(t_quaternion q, t_vec3 v)
{
	t_quaternion	tmp;

	tmp = quat_mult_3(q, v);
	tmp = quat_mult_quat(tmp, invert_quat(q));
	return (tmp.v);
}

// t_vec4	vec4_normalize(t_vec4 v)
// {
// 	return (vec4_mult_scalar(v, vec4_rcp_length(v)));
// }

t_quaternion	init_quat(t_vec3 v, float w)
{
	t_quaternion	new_quat;
	// float			len;

	// v = vec3_normalize(v);
	new_quat.v = vec3_mult_scalar(v, MSIN(TORAD(w) * 0.5f));
	new_quat.w = MCOS(TORAD(w) * 0.5f);
	// len = 1 / sqrtf(1 + new_quat.w * new_quat.w);
	// new_quat.w *= len;
	// new_quat.v = vec3_mult_scalar(new_quat.v, len);
	normalise_quat(&new_quat);
	return (new_quat);

	// t_quaternion	quat;

	// quat = vec3_mult_scalar(v, MSIN(TORAD(w) * 0.5f));
	// quat.w = cosf(w * 0.5f);
	// return (vec4_normalize(quat));
}

void			normalise_quat(t_quaternion *q)
{
	float len;

	len = 1 / sqrtf(q->w * q->w + vec3_dot(q->v, q->v));
	q->w *= len;
	q->v = vec3_mult_scalar(q->v, len);
}
