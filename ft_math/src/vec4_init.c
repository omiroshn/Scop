/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:48:42 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/25 16:48:43 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vecf.h"

inline t_vec4	vec4_init(float x, float y, float z, float w)
{
	return ((t_vec4){{{x, y, z, w}}});
}

inline t_vec4	vec4_init_single(float x)
{
	return ((t_vec4){{{x, x, x, x}}});
}

inline t_vec4	vec4_add(t_vec4 v1, t_vec4 v2)
{
	t_vec4 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	result.w = v1.w + v2.w;
	return (result);
}

inline t_vec4	vec4_mult(t_vec4 v1, t_vec4 v2)
{
	t_vec4 result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	result.w = v1.w * v2.w;
	return (result);
}
