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

t_vec4	cut_vertex_string(char *line)
{
	char	*cutted;
	char	**sub;
	t_vec4	vec;

	cutted = ft_strsub(line, 2, ft_strlen(line));
	sub = ft_strsplit(cutted, ' ');
	if (!sub)
		vec = vec4_init(0.0f, 0.0f, 0.0f, 1.0f);
	else
	{
		if (get_size(sub) == 1)
			vec = vec4_init(sub[0] ? atof(sub[0]) : 0.0f,
				sub[1] ? atof(sub[1]) : 0.0f, 0.0f, 1.0f);
		else
			vec = vec4_init(sub[0] ? atof(sub[0]) : 0.0f,
				sub[1] ? atof(sub[1]) : 0.0f,
				sub[2] ? atof(sub[2]) : 0.0f, 1.0f);
		free_strsplit(sub);
	}
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
	if (!sub)
		vec = vec2_init(0.0f, 0.0f);
	else
	{
		vec = vec2_init(
			sub[0] ? atof(sub[0]) : 0.0f,
			sub[1] ? atof(sub[1]) : 0.0f);
		free_strsplit(sub);
	}
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
	if (!sub)
		vec = vec3_init(0.0f, 0.0f, 0.0f);
	else
	{
		if (get_size(sub) == 1)
			vec = vec3_init(sub[0] ? atof(sub[0]) : 0.0f,
				sub[1] ? atof(sub[1]) : 0.0f, 0.0f);
		else
			vec = vec3_init(sub[0] ? atof(sub[0]) : 0.0f,
				sub[1] ? atof(sub[1]) : 0.0f,
				sub[2] ? atof(sub[2]) : 0.0f);
		free_strsplit(sub);
	}
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
	if (sub)
	{
		i = 0;
		while (++i < get_size(sub) - 1)
		{
			parse(v, sub[0], (*faces_count)++);
			parse(v, sub[i], (*faces_count)++);
			parse(v, sub[i + 1], (*faces_count)++);
		}
		free_strsplit(sub);
	}
	free(cutted);
	free(trimmed);
}
