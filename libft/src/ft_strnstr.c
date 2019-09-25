/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 21:29:52 by omiroshn          #+#    #+#             */
/*   Updated: 2017/10/29 21:29:53 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;

	if (!*little)
		return ((char*)big);
	i = -1;
	while (big[++i] && i < len)
	{
		j = 0;
		while (little[j] && big[i + j] && (i + j) < len)
		{
			if (big[i + j] == little[j])
				j++;
			else
				break ;
		}
		if (little[j] == 0)
			return ((char*)(big + i));
	}
	return (NULL);
}
