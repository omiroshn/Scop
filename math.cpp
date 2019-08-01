#include "ft_math.h"

t_vec4	vec4_init_single(float x)
{
	return ((t_vec4){{x, x, x, x}});
}
t_vec4	vec4_init_m128(__m128 m128)
{
	return ((t_vec4){.m128 = m128});
}
t_vec4	vec4_init_vec3(t_vec3 v, float value)
{
	return ((t_vec4){{v.x, v.y, v.z, value}});
}
float	ft_rsqrt(const float x)
{
	const __m128 a = _mm_set_ss(x);
	const __m128 r = _mm_rsqrt_ss(a);

	return (_mm_cvtss_f32(
				_mm_add_ss(
					_mm_mul_ss(_mm_set_ss(1.5f), r),
					_mm_mul_ss(
						_mm_mul_ss(
							_mm_mul_ss(
								a,
								_mm_set_ss(-0.5f)),
							r),
						_mm_mul_ss(r, r)))));
}
float	vec4_dot(t_vec4 v1, t_vec4 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}
float	vec4_rcp_length(t_vec4 v)
{
	const float d = vec4_dot(v, v);

	return (ft_rsqrt(d));
}
t_vec4	vec4_mult(t_vec4 v1, t_vec4 v2)
{
	return (vec4_init_m128(_mm_mul_ps(v1.m128, v2.m128)));
}
t_vec4	vec4_mult_scalar(t_vec4 v, float c)
{
	return (vec4_mult(v, vec4_init_single(c)));
}
t_vec4	vec4_normalize(t_vec4 v)
{
	return (vec4_mult_scalar(v, vec4_rcp_length(v)));
}
float	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
t_vec3	vec3_init(float x, float y, float z)
{
	return ((t_vec3){{x, y, z, 0.0f}});
}
t_vec3	vec3_init_single(float x)
{
	return ((t_vec3){{x, x, x, 0.0f}});
}
t_vec3	vec3_init_m128(__m128 m128)
{
	return ((t_vec3){.m128 = m128});
}

t_vec3	vec3_mult(t_vec3 v1, t_vec3 v2)
{
	return (vec3_init_m128(_mm_mul_ps(v1.m128, v2.m128)));
}
t_vec3	vec3_mult_scalar(t_vec3 v, float c)
{
	return (vec3_mult(v, vec3_init_single(c)));
}
t_quaternion		init_quat_rad(t_vec3 v, float w)
{
	t_quaternion	quat;

	quat = vec3_mult_scalar(v, sin(w * 0.5f));
	quat.w = cosf(w * 0.5f);
	return (vec4_normalize(quat));
}
t_quaternion		init_quat_deg(t_vec3 v, float w)
{
	return (init_quat_rad(v, TORAD(w)));
}
float	vec3_rcp_length(t_vec3 v)
{
	const float d = vec3_dot(v, v);

	return (ft_rsqrt(d));
}
t_vec3	vec3_normalize(t_vec3 v)
{
	return (vec3_mult_scalar(v, vec3_rcp_length(v)));
}
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	return (vec3_init_m128(_mm_add_ps(v1.m128, v2.m128)));
}
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	return (vec3_init_m128(_mm_sub_ps(v1.m128, v2.m128)));
}
t_vec3	vec3_div(t_vec3 v1, t_vec3 v2)
{
	return (vec3_init_m128(_mm_div_ps(v1.m128, v2.m128)));
}
#include <pmmintrin.h>

t_quaternion		invert_quat(t_quaternion q)
{
	q = vec4_mult_scalar(q, -1.0f);
	q.w *= -1.0f;
	return (q);
}
t_quaternion		quat_mult_quat(t_quaternion xyzw, t_quaternion abcd)
{
	__m128 wzyx = _mm_shuffle_ps(xyzw.m128, xyzw.m128, _MM_SHUFFLE(0,1,2,3));
	__m128 baba = _mm_shuffle_ps(abcd.m128, abcd.m128, _MM_SHUFFLE(0,1,0,1));
	__m128 dcdc = _mm_shuffle_ps(abcd.m128, abcd.m128, _MM_SHUFFLE(2,3,2,3));
	__m128 ZnXWY = _mm_hsub_ps(_mm_mul_ps(xyzw.m128, baba),
								_mm_mul_ps(wzyx, dcdc));
	__m128 XZYnW = _mm_hadd_ps(_mm_mul_ps(xyzw.m128, dcdc),
								_mm_mul_ps(wzyx, baba));
	__m128 XZWY = _mm_addsub_ps(
					_mm_shuffle_ps(XZYnW, ZnXWY, _MM_SHUFFLE(3,2,1,0)),
					_mm_shuffle_ps(ZnXWY, XZYnW, _MM_SHUFFLE(2,3,0,1)));

	return vec4_init_m128(_mm_shuffle_ps(XZWY, XZWY, _MM_SHUFFLE(2,1,3,0)));
}
t_quaternion		quat_mult_vec3(t_quaternion q, t_vec3 v)
{
	t_quaternion	res;

	res.x = q.y * v.z - q.z * v.y;
	res.y = q.z * v.x - q.x * v.z;
	res.z = q.x * v.y - q.y * v.x;
	res = vec3_add(vec3_mult_scalar(v, q.w), res);
	res.w = -1.0f * vec3_dot(q, v);
	return (res);
}
t_vec3			quat_transform_vec3(t_quaternion q, t_vec3 v)
{
	return (vec3_normalize(quat_mult_quat(
								quat_mult_vec3(q, v),
								invert_quat(q))));
}
t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	__m128 a_yzx;
	__m128 b_yzx;
	__m128 c;

	a_yzx = _mm_shuffle_ps(v1.m128, v1.m128, _MM_SHUFFLE(3, 0, 2, 1));
	b_yzx = _mm_shuffle_ps(v2.m128, v2.m128, _MM_SHUFFLE(3, 0, 2, 1));
	c = _mm_sub_ps(_mm_mul_ps(v1.m128, b_yzx),
							_mm_mul_ps(a_yzx, v2.m128));
	return (vec3_init_m128(_mm_shuffle_ps(c, c, _MM_SHUFFLE(3, 0, 2, 1))));
}
