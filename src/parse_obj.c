/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:50:23 by omiroshn          #+#    #+#             */
/*   Updated: 2019/10/15 18:50:23 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int	ft_array_length(char const *s, char c)
{
	unsigned int len;

	len = 0;
	while (*s)
	{
		if (*s == c)
			++s;
		else
		{
			++len;
			while (*s && *s != c)
				++s;
		}
	}
	return (len);
}

static int	ft_chrcnt(char *line, char c)
{
	int i;
	int cnt;

	cnt = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == c)
			cnt++;
	}
	return (cnt);
}

void		parse(GLushort *vertex_indices, GLushort *uv_indices,
			GLushort *normal_indices, char *line, int index)
{
	char	**s1;
	int		slashes;
	int		tmp_size;

	slashes = ft_chrcnt(line, '/');
	if (slashes)
	{
		s1 = ft_strsplit(line, '/');
		tmp_size = ft_array_length(line, '/');
		vertex_indices[index] = atoi(s1[0]);
		if (slashes == 1 || tmp_size == 3)
			uv_indices[index] = atoi(s1[1]);
		if (slashes == 2 || tmp_size == 2)
			normal_indices[index] = atoi(s1[tmp_size == 2 ? 1 : 2]);
		free_strsplit(s1);
	}
	else
		vertex_indices[index] = line ? atoi(line) : 4;
}
