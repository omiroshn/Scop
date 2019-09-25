/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:27:53 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/25 17:27:53 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

const t_mat4 g_identity_mat4 =
{
	.col =
	{
		(t_vec4){{{1.0f, 0.0f, 0.0f, 0.0f}}},
		(t_vec4){{{0.0f, 1.0f, 0.0f, 0.0f}}},
		(t_vec4){{{0.0f, 0.0f, 1.0f, 0.0f}}},
		(t_vec4){{{0.0f, 0.0f, 0.0f, 1.0f}}}
	}
};

inline t_mat4		mat4_from_vec4(t_vec4 *v)
{
	return ((t_mat4){{{{v[0], v[1], v[2], v[3]}}}});
}

inline t_mat4		mat4_with_value(float value)
{
	const t_vec4 vec = vec4_init_single(value);

	return ((t_mat4){{{{vec, vec, vec, vec}}}});
}

inline t_mat4		mat4_identity(void)
{
	return (g_identity_mat4);
}