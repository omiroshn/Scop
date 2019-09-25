/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:51:23 by omiroshn          #+#    #+#             */
/*   Updated: 2017/10/26 15:51:25 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	char			*dest;
	unsigned char	*str;

	dest = dst;
	str = (unsigned char *)src;
	i = -1;
	while (++i < n)
	{
		dest[i] = str[i];
		if (str[i] == (unsigned char)c)
			return (&dest[i + 1]);
	}
	return (NULL);
}
