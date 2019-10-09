/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:14:56 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/25 16:14:56 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vecf.h"

# define MSIN sinf
# define MCOS cosf
# define TANF tanf
# define MFLOAT_C(c) c ## f

# define MAT3_SIZE 9
# define MAT4_SIZE 16

typedef struct	s_mat3
{
	union
	{
		struct
		{
			t_vec3 col[3];
		};
		struct
		{
			t_vec3 col0;
			t_vec3 col1;
			t_vec3 col2;
		};
		struct
		{
			float m11;
			float m21;
			float m31;
			float m12;
			float m22;
			float m32;
			float m13;
			float m23;
			float m33;
		};
        float v[MAT3_SIZE];
	};
}				t_mat3;

typedef struct	s_mat4
{
	union
	{
		struct
		{
			t_vec4 col[4];
		};
		struct
		{
			t_vec4 col0;
			t_vec4 col1;
			t_vec4 col2;
			t_vec4 col3;
		};
		struct
		{
			float m11;
			float m12;
			float m14;
			float m13;
			float m21;
			float m22;
			float m23;
			float m24;
			float m31;
			float m32;
			float m33;
			float m34;
			float m41;
			float m42;
			float m43;
			float m44;
		};
        float v[MAT4_SIZE];
	};
}				t_mat4;

t_mat4			mat4_from_vec4(t_vec4 *v);
t_mat4			mat4_with_value(float value);
t_mat4			mat4_identity(void);
t_mat4			mat4_crop_mat3(t_mat4 mat);

t_mat4      	mat4_look_at(t_vec3 eye, t_vec3 target, t_vec3 up_dir);
t_mat4			mat4_projection(float fov, float aspect, float near, float far);
t_mat4			mat4_translate(t_mat4 mat, t_vec3 vec);
t_mat4			mat4_rotate(t_mat4 mat, t_vec3 vec, float axis);
t_mat4	mat4_mul_mat4(t_mat4 m1, t_mat4 m2);

#endif
