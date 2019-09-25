/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:40:58 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/25 17:40:58 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vecf.h"

inline t_vec3 vec3_add(t_vec3 v1, t_vec3 v2)
{
    t_vec3 result;

    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return (result);
}

inline t_vec3 vec3_sub(t_vec3 v1, t_vec3 v2)
{
    t_vec3 result;

    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return (result);
}

inline t_vec3 vec3_mult(t_vec3 v1, t_vec3 v2)
{
    t_vec3 result;

    result.x = v1.x * v2.x;
    result.y = v1.y * v2.y;
    result.z = v1.z * v2.z;
    return (result);
}

inline t_vec3 vec3_div(t_vec3 v1, t_vec3 v2)
{
    t_vec3 result;

    result.x = v1.x / v2.x;
    result.y = v1.y / v2.y;
    result.z = v1.z / v2.z;
    return (result);
}
