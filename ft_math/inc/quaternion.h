/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:21:29 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/25 16:21:30 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

# define TORAD(x) ((x) * 0.017453293f)
# include "vecf.h"

typedef t_vec4	t_quaternion;

t_quaternion		quat_init_rad(t_vec3 v, float w);
t_quaternion		quat_init_normalizing_rad(t_vec3 v, float w);
t_quaternion		quat_init_deg(t_vec3 v, float w);
t_quaternion		quat_init_normalizing_deg(t_vec3 v, float w);

t_quaternion		invert_quat(t_quaternion q);
t_quaternion		quat_mult_quat(t_quaternion xyzw, t_quaternion abcd);
t_quaternion		quat_mult_vec3(t_quaternion q, t_vec3 v);
t_vec3			    quat_transform_vec3(t_quaternion q, t_vec3 v);

#endif
