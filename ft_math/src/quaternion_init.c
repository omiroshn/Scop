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

inline t_quaternion		quat_init_rad(t_vec3 v, float w)
{
	t_quaternion	quat;

	quat = vec3_mult_scalar(v, sin(w * 0.5f));
	quat.w = cosf(w * 0.5f);
	return (vec4_normalize(quat));
}

inline t_quaternion		quat_init_normalizing_rad(t_vec3 v, float w)
{
	return (quat_init_rad(vec3_normalize(v), w));
}

inline t_quaternion		quat_init_deg(t_vec3 v, float w)
{
	return (quat_init_rad(v, TORAD(w)));
}

inline t_quaternion		quat_init_normalizing_deg(t_vec3 v, float w)
{
	return (quat_init_rad(vec3_normalize(v), TORAD(w)));
}
