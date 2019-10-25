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

void		parse(t_tmp_vertex *v, char *line, int index)
{
	v->slashes = ft_chrcnt(line, '/');
	if (v->slashes)
	{
		v->len = ft_array_length(line, '/');
		if (v->len == 0 || v->len == 1)
			v->vertex_indices[index] = 0;
		else
		{
			v->sub = ft_strsplit(line, '/');
			v->vertex_indices[index] = v->sub[0] ? atoi(v->sub[0]) : 0;
			if (v->slashes == 1 || v->len == 3)
				v->uv_indices[index] = v->sub[1] ? atoi(v->sub[1]) : 0;
			if (v->slashes == 2 || v->len == 2)
			{
				if (v->len == 2)
					v->normal_indices[index] = v->sub[1] ? atoi(v->sub[1]) : 0;
				else
					v->normal_indices[index] = v->sub[2] ? atoi(v->sub[2]) : 0;
			}
			free_strsplit(v->sub);
		}
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
	if (!sub)
		return (0);
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
	int		f_chars;

	f_chars = 0;
	ft_printf("Reading: %s\n", filename);
	if ((fd = open(filename, O_RDONLY)) < 0 || read(fd, NULL, 0) < 0)
		put_error("Failed to open file.");
	faces = 0;
	while (get_next_line(fd, &line))
	{
		if (!(ft_strncmp(line, "f ", 2)))
		{
			faces += get_faces(line);
			f_chars++;
		}
		free(line);
	}
	close(fd);
	if (f_chars < 10)
		put_error("Invalid obj file.");
	return (faces);
}
