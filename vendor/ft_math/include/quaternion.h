/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 09:09:07 by admin             #+#    #+#             */
/*   Updated: 2018/08/14 09:13:31 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

# include "vecf.h"

typedef t_vec4	t_quaternion;

t_quaternion		init_quat_rad(t_vec3 v, float w);
t_quaternion		init_quat_normalizing_rad(t_vec3 v, float w);
t_quaternion		init_quat_deg(t_vec3 v, float w);
t_quaternion		init_quat_normalizing_deg(t_vec3 v, float w);

t_quaternion		invert_quat(t_quaternion q);
t_quaternion		quat_mult_quat(t_quaternion q1, t_quaternion q2);
t_quaternion		quat_mult_vec3(t_quaternion q, t_vec3 v);
t_vec3			quat_transform_vec3(t_quaternion q, t_vec3 v);

#endif

