/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_mvp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:35:23 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/25 17:35:25 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mat4  look_at(t_vec3 eye, t_vec3 target, t_vec3 up_dir)
{
    t_vec3 forward = vec3_normalize(vec3_sub(eye, target));
	t_vec3 left = vec3_normalize(vec3_cross(up_dir, forward));
	t_vec3 up = vec3_cross(forward, left);

    t_mat4 matrix = mat4_identity();

    matrix.m11 = left.x;
	matrix.m21 = left.y;
	matrix.m31 = left.z;
	matrix.m12 = up.x;
	matrix.m22 = up.y;
	matrix.m32 = up.z;
	matrix.m13 = forward.x;
	matrix.m23 = forward.y;
	matrix.m33 = forward.z;

	matrix.m13 = -left.x * eye.x - left.y * eye.y - left.z * eye.z;
	matrix.m23 = -up.x * eye.x - up.y * eye.y - up.z * eye.z;
	matrix.m33 = -forward.x * eye.x - forward.y * eye.y - forward.z * eye.z;
    return (matrix);
}
