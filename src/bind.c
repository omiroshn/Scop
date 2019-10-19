/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:56:25 by omiroshn          #+#    #+#             */
/*   Updated: 2019/10/15 18:56:25 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "stb_image.h"

static void		for_each(const char **cubemap_faces)
{
	int				i;
	unsigned char	*data;
	int				m_w;
	int				m_h;
	int				m_bpp;

	m_w = 0;
	m_h = 0;
	m_bpp = 0;
	i = -1;
	while (++i < 6)
	{
		data = stbi_load(cubemap_faces[i], &m_w, &m_h, &m_bpp, 4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGBA, m_w, m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		free(data);
	}
}

unsigned int	bind_cubemap(void)
{
	const char		*cubemap_faces[] = {
		"res/models/Yokohama/posx.jpg",
		"res/models/Yokohama/negx.jpg",
		"res/models/Yokohama/posy.jpg",
		"res/models/Yokohama/negy.jpg",
		"res/models/Yokohama/posz.jpg",
		"res/models/Yokohama/negz.jpg",
	};
	unsigned int	texture_id;

	glGenTextures(1, &texture_id);
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
	stbi_set_flip_vertically_on_load(0);
	for_each(cubemap_faces);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return (texture_id);
}

unsigned int	bind_texture(char *path)
{
	unsigned int	texture_id;
	int				m_w;
	int				m_h;
	int				m_bpp;
	unsigned char	*data;

	stbi_set_flip_vertically_on_load(1);
	glGenTextures(1, &texture_id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	data = stbi_load(path, &m_w, &m_h, &m_bpp, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_w, m_h, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	free(data);
	return (texture_id);
}

t_binded		set_up_object(t_vertex *vertices, int size)
{
	unsigned int vao;
	unsigned int vbo;
	unsigned int program;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(t_vertex),
			&vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
			sizeof(t_vertex), (void*)get_offset(t_vertex, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
			sizeof(t_vertex), (void*)get_offset(t_vertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
			sizeof(t_vertex), (void*)get_offset(t_vertex, tex_coords));
	program = read_shaders(
		"res/shaders/vertex_shader.glsl",
		"res/shaders/fragment_shader.glsl");
	return (t_binded){vao, program};
}

t_binded		set_up_skybox(t_vertex *vertices, int size)
{
	unsigned int vao;
	unsigned int vbo;
	unsigned int program;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(t_vertex),
			&vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
			sizeof(t_vertex), (void*)get_offset(t_vertex, position));
	program = read_shaders(
		"res/shaders/skybox.vt.glsl",
		"res/shaders/skybox.fg.glsl");
	return (t_binded){vao, program};
}
