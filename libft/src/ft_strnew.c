/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:00:18 by omiroshn          #+#    #+#             */
/*   Updated: 2017/10/31 16:00:21 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t		i;
	char		*str;

	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = -1;
	while (++i < size)
		str[i] = '\0';
	str[i] = '\0';
	return (str);
}
