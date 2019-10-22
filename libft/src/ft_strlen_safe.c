/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_safe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:29:45 by omiroshn          #+#    #+#             */
/*   Updated: 2019/10/21 17:29:45 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlen_safe(const char *str)
{
	char *s;

	if (!str || str[0] == 0)
		return (0);
	s = (char*)str;
	while (*s)
		++s;
	return ((size_t)(s - str));
}
