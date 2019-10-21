/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 18:04:16 by omiroshn          #+#    #+#             */
/*   Updated: 2019/10/16 18:04:16 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

// float	ft_atof(const char *str)
// {
// 	float	res;
// 	float	res2;
// 	char	*c;
// 	int		len;

// 	c = (char *)str;
// 	res = (float)ft_atoi(c);
// 	while (*c && *c != '.')
// 		c++;
// 	if (*c == '.')
// 		c++;
// 	res2 = (float)ft_atoi(c);
// 	len = ft_strlen(c);
// 	while (len--)
// 		res2 /= 10;
// 	return (res + ((res > 0) ? res2 : -res2));
// }

float		ft_atof(const char *str)
{
	float	n;
	int		i;
	int		k;
	int		signe;

	i = 0;
	n = 0;
	k = 0;
	signe = 1;
	if (!str)
		return (0);
	while (str[i] == ' ' || str[i] == '\v' || str[i] == '\t' || str[i] == '\r'
			|| str[i] == '\f' || str[i] == '\n')
		i++;
	signe = (str[i] == '-') ? -signe : signe;
	i = (str[i] == '-' || str[i] == '+') ? i + 1 : i;
	while (str[i] > 47 && str[i] < 58)
	{
		n = n * 10 + (str[i++] - 48);
		if (str[i] == '.')
			k = i++;
	}
	while (k != 0 && str[++k])
		signe = signe * 10;
	return (n / signe);
}


t_vec4	cut_vertex_string(char *line)
{
	char	*cutted;
	char	**sub;
	t_vec4	vec;

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	cutted = ft_strsub(line, 2, ft_strlen(line));
	sub = ft_strsplit(cutted, ' ');
	if (sub[0] != NULL)
		x = ft_atof(sub[0]);
	if (sub[1] != NULL)
		y = ft_atof(sub[1]);
	if (sub[2] != NULL)
		z = ft_atof(sub[2]);
	vec = vec4_init(x, y, z, 1.0f);
	free_strsplit(sub);
	free(cutted);
	return (vec);
}

t_vec2	cut_texture_string(char *line)
{
	char	*cutted;
	char	**sub;
	t_vec2	vec;

	cutted = ft_strsub(line, 3, ft_strlen(line));
	sub = ft_strsplit(cutted, ' ');
	vec = vec2_init(sub[0] ? atof(sub[0]) : 0.0f,
		sub[1] ? atof(sub[1]) : 0.0f);
	free_strsplit(sub);
	free(cutted);
	return (vec);
}

t_vec3	cut_normal_string(char *line)
{
	char	*cutted;
	char	**sub;
	t_vec3	vec;

	cutted = ft_strsub(line, 3, ft_strlen(line));
	sub = ft_strsplit(cutted, ' ');
	vec = vec3_init(sub[0] ? atof(sub[0]) : 0.0f,
		sub[1] ? atof(sub[1]) : 0.0f,
		sub[2] ? atof(sub[2]) : 0.0f);
	free_strsplit(sub);
	free(cutted);
	return (vec);
}

void	cut_face_string(t_tmp_vertex *v, char *line, int *faces_count)
{
	char	*cutted;
	char	*trimmed;
	char	**sub;
	int		i;

	cutted = ft_strsub(line, 2, ft_strlen(line));
	trimmed = ft_strtrim(cutted);
	sub = ft_strsplit(trimmed, ' ');
	i = 0;
	while (++i < get_size(sub) - 1)
	{
		parse(v, sub[0], (*faces_count)++);
		parse(v, sub[i], (*faces_count)++);
		parse(v, sub[i + 1], (*faces_count)++);
	}
	free(cutted);
	free_strsplit(sub);
	free(trimmed);
}
