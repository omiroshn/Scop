/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:16:19 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/25 16:16:19 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vecf.h"

inline t_vec3	vec3_init(float x, float y, float z)
{
    return ((t_vec3){{{x, y, z}}});
}

inline t_vec3	vec3_init_single(float x)
{
    return ((t_vec3){{{x, x, x}}});
}
