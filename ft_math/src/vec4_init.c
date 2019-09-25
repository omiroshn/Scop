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
