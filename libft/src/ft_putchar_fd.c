/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 22:07:26 by omiroshn          #+#    #+#             */
/*   Updated: 2017/11/01 22:07:27 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_unicode(char c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putchar_fd(int c, int fd)
{
	if (c <= 0x7F)
		print_unicode(c, fd);
	else if (c <= 0x7FF)
	{
		print_unicode((c >> 6) + 0xC0, fd);
		print_unicode((c & 0x3F) + 0x80, fd);
	}
	else if (c <= 0xFFFF)
	{
		print_unicode((c >> 12) + 0xE0, fd);
		print_unicode(((c >> 6) & 0x3F) + 0x80, fd);
		print_unicode((c & 0x3F) + 0x80, fd);
	}
	else if (c <= 0x10FFFF)
	{
		print_unicode((c >> 18) + 0xF0, fd);
		print_unicode(((c >> 12) & 0x3F) + 0x80, fd);
		print_unicode(((c >> 6) & 0x3F) + 0x80, fd);
		print_unicode((c & 0x3F) + 0x80, fd);
	}
}
