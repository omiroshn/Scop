/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 16:48:33 by omiroshn          #+#    #+#             */
/*   Updated: 2017/10/27 16:48:35 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;
	size_t	len1;

	i = 0;
	len = 0;
	len1 = ft_strlen(dst);
	while (dst[len] && len < size)
		len++;
	if (len >= size)
		return (size + ft_strlen(src));
	while (src[i] && i < (size - len1 - 1))
	{
		dst[len + i] = ((char *)src)[i];
		i++;
	}
	dst[len + i] = '\0';
	return (len + ft_strlen(src));
}
