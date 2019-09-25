/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 22:03:37 by omiroshn          #+#    #+#             */
/*   Updated: 2017/11/03 22:03:39 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countwords(char *str, char sep)
{
	int	i;
	int	result;

	if (!str)
		return (0);
	i = 0;
	result = 0;
	if (str[0] != sep)
		result++;
	while (++i && str[i])
		if (str[i] != sep && str[i - 1] == sep)
			result++;
	return (result);
}
