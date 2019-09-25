/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:48:47 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/25 16:48:47 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vecf.h"

inline t_vec2	vec2_init(float x, float y)
{
    return ((t_vec2){{{x, y}}});
}

inline t_vec2	vec2_init_single(float x)
{
    return ((t_vec2){{{x, x}}});
}
