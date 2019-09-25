/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 21:55:39 by omiroshn          #+#    #+#             */
/*   Updated: 2017/10/30 21:55:40 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*m;
	size_t	i;

	if (!(m = malloc(size)))
		return (NULL);
	i = -1;
	while (++i < size)
		((unsigned char*)m)[i] = '\0';
	return (m);
}
