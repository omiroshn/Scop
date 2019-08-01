/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Admin <Admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 01:49:29 by admin             #+#    #+#             */
/*   Updated: 2018/08/31 21:13:43 by Admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALAR_H
# define SCALAR_H

# include <stdbool.h>
# include <inttypes.h>

# define MAX(a, b) ((a) > (b) ? (a) : (b))
# define MIN(a, b) ((a) < (b) ? (a) : (b))
# define TORAD(x) ((x) * 0.017453293f)
# define TODEG(x) ((x) * 57.2957795f)

bool			float_equal_float(float f1, float f2);

float			ft_rsqrt(const float x);

float			madd(const float a, const float b, const float c);
float			msub(const float a, const float b, const float c);
float			nmadd(const float a, const float b, const float c);
float			nmsub(const float a, const float b, const float c);

uint32_t		clamp_u32(uint32_t value, uint32_t edge0, uint32_t edge1);
uint16_t		clamp_u16(uint16_t value, uint16_t edge0, uint16_t edge1);
int32_t			clamp_32(int32_t value, int32_t edge0, int32_t edge1);
int16_t			clamp_16(int16_t value, int16_t edge0, int16_t edge1);

uint32_t		min_u32(uint32_t rhs, uint32_t lhs);
uint16_t		min_u16(uint16_t rhs, uint16_t lhs);
uint32_t		max_u32(uint32_t rhs, uint32_t lhs);
uint16_t		max_u16(uint16_t rhs, uint16_t lhs);

int32_t			min_32(int32_t rhs, int32_t lhs);
int16_t			min_16(int16_t rhs, int16_t lhs);
int32_t			max_32(int32_t rhs, int32_t lhs);
int16_t			max_16(int16_t rhs, int16_t lhs);

#endif
