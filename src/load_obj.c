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

void	init_temp_struct(t_tmp_vertex *v, int size)
{
	v->vertex = ft_memalloc(sizeof(t_vec4) * size);
	v->uv = ft_memalloc(sizeof(t_vec2) * size);
	v->normal = ft_memalloc(sizeof(t_vec3) * size);
	v->vertex_indices = ft_memalloc(sizeof(GLushort) * size);
	v->uv_indices = ft_memalloc(sizeof(GLushort) * size);
	v->normal_indices = ft_memalloc(sizeof(GLushort) * size);
	v->vertex_count = 0;
	v->texture_count = 0;
	v->normal_count = 0;
	v->faces_count = 0;
}

void	free_tmp_struct(t_tmp_vertex *v)
{
	free(v->vertex);
	free(v->uv);
	free(v->normal);
	free(v->vertex_indices);
	free(v->uv_indices);
	free(v->normal_indices);
}

void	fill_vertex_array(t_vertex *vertices, t_tmp_vertex v, int size)
{
	int			j;
	int			i;
	t_vertex	vertex;

	j = 0;
	while (j < size && (i = -1))
	{
		while (++i < 3)
		{
			vertex.position = v.vertex[v.vertex_indices[j + i] - 1];
			vertex.normal = vec3_init(0.0f, 0.0f, 0.0f);
			vertex.tex_coords = vec2_init(0.0f, 0.0f);
			vertex.normal = v.normal[v.normal_indices[j + i] - 1];
			if (&v.normal[0] == NULL)
			{
				vertex.normal.x = KOEF(v.vertex[v.vertex_indices[j + i] - 1].x);
				vertex.normal.y = KOEF(v.vertex[v.vertex_indices[j + i] - 1].y);
				vertex.normal.z = KOEF(v.vertex[v.vertex_indices[j + i] - 1].z);
			}
			if (&v.uv[0] != NULL)
				vertex.tex_coords = v.uv[v.uv_indices[j + i] - 1];
			vertices[j + i] = vertex;
		}
		j += 3;
	}
}

void	load_obj(t_timer *timer, char *filename, t_vertex *vertices, int size)
{
	int				fd;
	char			*line;
	t_tmp_vertex	v;

	fd = open(filename, O_RDONLY);
	init_temp_struct(&v, size);
	while (get_next_line(fd, &line))
	{
		if (!(ft_strncmp(line, "v ", 2)))
			v.vertex[v.vertex_count++] = cut_vertex_string(line);
		else if (!(ft_strncmp(line, "vt ", 3)))
			v.uv[v.texture_count++] = cut_texture_string(line);
		else if (!(ft_strncmp(line, "vn ", 3)))
			v.normal[v.normal_count++] = cut_normal_string(line);
		else if (!(ft_strncmp(line, "f ", 2)))
			cut_face_string(&v, line, &v.faces_count);
		free(line);
	}
	fill_vertex_array(vertices, v, size);
	update_time(timer);
	ft_printf("%s done in %.2f seconds\n", filename, timer->delta_time);
	free_tmp_struct(&v);
}
