/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:14:38 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/25 16:14:40 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECF_H
#define VECF_H

#include <math.h>

#define VEC2_SIZE 2
#define VEC3_SIZE 3
#define VEC4_SIZE 4

#define MSQRT sqrtf

typedef struct  s_vec2
{
	union
    {
		struct
        {
			float x;
			float y;
		};
		float v[VEC2_SIZE];
	};
}				t_vec2;

t_vec2	vec2_init(float x, float y);
t_vec2	vec2_init_single(float x);

typedef struct	s_vec3
{
	union
	{
		struct
		{
			float x;
            float y;
            float z;
		};
		float v[VEC3_SIZE];
	};
}				t_vec3;

t_vec3	vec3_init(float x, float y, float z);
t_vec3	vec3_init_single(float x);

t_vec3 vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3 vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3 vec3_mult(t_vec3 v1, t_vec3 v2);
t_vec3 vec3_div(t_vec3 v1, t_vec3 v2);

t_vec3      vec3_cross(t_vec3 v1, t_vec3 v2);
float       vec3_dot(t_vec3 v1, t_vec3 v2);
float       vec3_length(t_vec3 v);
float       vec3_distance(t_vec3 v1, t_vec3 v2);
t_vec3      vec3_mult_scalar(t_vec3 v, float c);
t_vec3      vec3_normalize_safe(t_vec3 v);
t_vec3      vec3_normalize(t_vec3 v);

typedef struct	s_vec4
{
	union
	{
		struct
		{
			float x;
            float y;
            float z;
			float w;
		};
		float v[VEC4_SIZE];
	};
}				t_vec4;

t_vec4	vec4_init(float x, float y, float z, float w);
t_vec4	vec4_init_single(float x);

#endif
