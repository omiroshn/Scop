/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 21:10:01 by omiroshn          #+#    #+#             */
/*   Updated: 2017/11/26 17:55:42 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_joinstr(char **line, t_gnl *gnl, char *end)
{
	char	*temp;
	char	*temp2;

	if (end)
	{
		temp = ft_strsub(gnl->content, 0, end - gnl->content);
		gnl->size -= (end - gnl->content) + 1;
		ft_memmove(gnl->content, end + 1, gnl->size + 1);
	}
	else
	{
		temp = ft_strdup(gnl->content);
		gnl->size = 0;
	}
	temp2 = *line;
	if (temp2)
	{
		*line = ft_strjoin(temp2, temp);
		free(temp2);
		free(temp);
	}
	else
		*line = temp;
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl	gnl[4500];
	char			*end;

	end = NULL;
	if (!line || (!(*line = 0) && (fd < 0 || fd > 4499))
		|| read(fd, NULL, 0) < 0)
		return (-1);
	while (!end)
	{
		if (!gnl[fd].size &&
			(gnl[fd].size = read(fd, gnl[fd].content, BUFF_SIZE)) < 1)
		{
			if (*line)
				return (1);
			else
				return (gnl[fd].size);
		}
		gnl[fd].content[gnl[fd].size] = '\0';
		end = ft_memchr(gnl[fd].content, '\n', gnl[fd].size);
		ft_joinstr(line, &gnl[fd], end);
	}
	return (1);
}
