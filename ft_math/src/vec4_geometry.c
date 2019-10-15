/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_geometry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:26 by omiroshn          #+#    #+#             */
/*   Updated: 2019/10/15 15:47:26 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vecf.h"

inline float	vec4_length(t_vec4 v)
{
	return (MSQRT(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

inline t_vec4	vec4_mult_scalar(t_vec4 v, float c)
{
	return (vec4_mult(v, vec4_init_single(c)));
}

inline t_vec4	vec4_normalize(t_vec4 v)
{
	return (vec4_mult_scalar(v, vec4_length(v)));
}

inline t_vec4	vec4_init_m128(__m128 m128)
{
	return ((t_vec4){.m128 = m128});
}
