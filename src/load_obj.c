/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 21:18:19 by omiroshn          #+#    #+#             */
/*   Updated: 2019/10/15 21:18:19 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	load_obj(t_timer *timer, const char *filename,
			t_vertex *vertices, int size)
{
	int		fd;
	char 	*line;
	char	**sub;
	char	*cutted;

	fd = open(filename, O_RDONLY);

	GLushort *vertexIndices = ft_memalloc(sizeof(GLushort) * size);
	GLushort *uvIndices = ft_memalloc(sizeof(GLushort) * size);
	GLushort *normalIndices = ft_memalloc(sizeof(GLushort) * size);

	t_vec4 *temp_positions = ft_memalloc(sizeof(t_vec4) * size);
	t_vec3 *temp_normals = ft_memalloc(sizeof(t_vec3) * size);
	t_vec2 *temp_tx = ft_memalloc(sizeof(t_vec2) * size);

	int vertex_count = 0;
	int texture_count = 0;
	int normal_count = 0;
	int faces_count = 0;
	while (get_next_line(fd, &line))
	{
		if (!(ft_strncmp(line, "v ", 2)))
		{
			cutted = ft_strsub(line, 2, ft_strlen(line));
			sub = ft_strsplit(cutted, ' ');

			temp_positions[vertex_count++] =
				vec4_init(atof(sub[0]), atof(sub[1]),atof(sub[2]),1.0f);
			free_strsplit(sub);
			free(cutted);
		}
		else if (!(ft_strncmp(line, "vt ", 3)))
		{
			cutted = ft_strsub(line, 3, ft_strlen(line));
			sub = ft_strsplit(cutted, ' ');
			
			temp_tx[texture_count++] = vec2_init(atof(sub[0]), atof(sub[1]));
			free_strsplit(sub);
			free(cutted);
		}
		else if (!(ft_strncmp(line, "vn ", 3)))
		{
			cutted = ft_strsub(line, 3, ft_strlen(line));
			sub = ft_strsplit(cutted, ' ');

			temp_normals[normal_count++] =
				vec3_init(atof(sub[0]), atof(sub[1]), atof(sub[2]));
			free_strsplit(sub);
			free(cutted);
		}
		else if (!(ft_strncmp(line, "f ", 2)))
		{
			cutted = ft_strsub(line, 2, ft_strlen(line));
			char *trimmed = ft_strtrim(cutted);
			sub = ft_strsplit(trimmed, ' ');
			int i = 0;
			while (++i < get_size(sub) - 1)
			{
				parse(vertexIndices, uvIndices, normalIndices, sub[0], faces_count++);
				parse(vertexIndices, uvIndices, normalIndices, sub[i], faces_count++);
				parse(vertexIndices, uvIndices, normalIndices, sub[i + 1], faces_count++);
				// ft_printf("\n");
			}
			free(cutted);
			free_strsplit(sub);
			free(trimmed);
		}
		free(line);
	}

	for (int v = 0; v < size; v += 3)
	{
		for (unsigned int i = 0; i < 3; i += 1)
		{
			t_vec4 vertex = temp_positions[vertexIndices[v + i] - 1];
			t_vec3 normal = vec3_init(0.0f,0.0f,0.0f);
			t_vec2 uv = vec2_init(0.0f,0.0f);

			if (&temp_normals[0] == NULL)
			{
				normal.x = (temp_positions[vertexIndices[v + i] - 1].x + 1.2)/2.4;
				normal.y = (temp_positions[vertexIndices[v + i] - 1].y + 1.2)/2.4;
				normal.z = (temp_positions[vertexIndices[v + i] - 1].z + 1.2)/2.4;
			}
			else
				normal = temp_normals[normalIndices[v + i] - 1];

			if (&temp_tx[0] != NULL)
				uv = temp_tx[uvIndices[v + i] - 1];
			
			t_vertex ver = {vertex, normal, uv};
			vertices[v + i] = ver;
		}
	}
	update_time(timer);
	printf("%s done in %.2f seconds\n", filename, timer->delta_time);
	free(temp_positions);
	free(temp_normals);
	free(temp_tx);
	free(vertexIndices);
	free(normalIndices);
	free(uvIndices);
}