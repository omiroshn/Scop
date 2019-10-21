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

void		parse(t_tmp_vertex *v, char *line, int index)
{
	char	**s1;
	int		slashes;
	int		tmp_size;

	slashes = ft_chrcnt(line, '/');
	if (slashes)
	{
		s1 = ft_strsplit(line, '/');
		tmp_size = ft_array_length(line, '/');
		v->vertex_indices[index] = s1[0] ? atoi(s1[0]) : 0;
		if (slashes == 1 || tmp_size == 3)
			v->uv_indices[index] = s1[1] ? atoi(s1[1]) : 0;
		if (slashes == 2 || tmp_size == 2)
		{
			if (tmp_size == 2)
				v->normal_indices[index] = s1[1] ? atoi(s1[1]) : 0;
			else
				v->normal_indices[index] = s1[2] ? atoi(s1[2]) : 0;
		}
		free_strsplit(s1);
	}
	else
		v->vertex_indices[index] = line ? atoi(line) : 4;
}

int			get_faces(char *line)
{
	char	*cutted;
	char	**sub;
	char	*trimmed;
	int		i;
	int		faces_count;

	faces_count = 0;
	cutted = ft_strsub(line, 2, ft_strlen(line));
	trimmed = ft_strtrim(cutted);
	sub = ft_strsplit(trimmed, ' ');
	i = 1;
	while (i++ < get_size(sub) - 1)
		faces_count += 3;
	free(cutted);
	free_strsplit(sub);
	free(trimmed);
	return (faces_count);
}

int			get_size_of_obj(char *filename)
{
	int		fd;
	char	*line;
	int		faces;

	ft_printf("Reading: %s\n", filename);
	if ((fd = open(filename, O_RDONLY)) < 0 || read(fd, NULL, 0) < 0)
		put_error("Failed to open file.");
	faces = 0;
	while (get_next_line(fd, &line))
	{
		if (!(ft_strncmp(line, "f ", 2)))
			faces += get_faces(line);
		free(line);
	}
	close(fd);
	ft_printf("faces_count: %d\n", faces);
	return (faces);
}
