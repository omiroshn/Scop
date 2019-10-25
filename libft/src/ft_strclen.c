/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 18:51:32 by omiroshn          #+#    #+#             */
/*   Updated: 2019/10/25 18:51:33 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strclen(const char *str, char c)
{
	char *s;

	if (!str)
		return (0);
	s = (char*)str;
	while (*s && *s != c)
		++s;
	return ((int)(s - str));
}
