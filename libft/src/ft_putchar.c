/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 20:20:33 by omiroshn          #+#    #+#             */
/*   Updated: 2017/10/29 20:21:20 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_unicode(char c)
{
	write(1, &c, 1);
}

void		ft_putchar(int c)
{
	if (c <= 0x7F)
		print_unicode(c);
	else if (c <= 0x7FF)
	{
		print_unicode((c >> 6) + 0xC0);
		print_unicode((c & 0x3F) + 0x80);
	}
	else if (c <= 0xFFFF)
	{
		print_unicode((c >> 12) + 0xE0);
		print_unicode(((c >> 6) & 0x3F) + 0x80);
		print_unicode((c & 0x3F) + 0x80);
	}
	else if (c <= 0x10FFFF)
	{
		print_unicode((c >> 18) + 0xF0);
		print_unicode(((c >> 12) & 0x3F) + 0x80);
		print_unicode(((c >> 6) & 0x3F) + 0x80);
		print_unicode((c & 0x3F) + 0x80);
	}
}
