/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 20:07:16 by omiroshn          #+#    #+#             */
/*   Updated: 2018/08/31 20:07:17 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_sort_argv(int argc, char **argv)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (++i < argc && (j = -1))
		while (++j < argc - i)
			if (ft_strcmp(argv[j], argv[j + 1]) > 0)
			{
				tmp = argv[j];
				argv[j] = argv[j + 1];
				argv[j + 1] = tmp;
			}
}
