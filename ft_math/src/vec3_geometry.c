/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_geometry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:39:07 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/25 17:39:08 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vecf.h"

inline t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3 cross;

	cross.x = v1.y * v2.z - v1.z * v2.y;
	cross.y = v1.z * v2.x - v1.x * v2.z;
	cross.z = v1.x * v2.y - v1.y * v2.x;
	return (cross);
}

inline float	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

inline float	vec3_length(t_vec3 v)
{
	return (MSQRT(v.x * v.x + v.y * v.y + v.z * v.z));
}

inline float	vec3_distance(t_vec3 v1, t_vec3 v2)
{
	return (vec3_length(vec3_sub(v1, v2)));
}

inline t_vec3	vec3_mult_scalar(t_vec3 v, float c)
{
	return (vec3_mult(v, vec3_init_single(c)));
}
