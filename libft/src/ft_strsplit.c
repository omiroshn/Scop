/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 20:57:48 by omiroshn          #+#    #+#             */
/*   Updated: 2017/11/01 20:57:50 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_getword(const char *s, char c, int *i)
{
	char	*str;
	int		k;

	if (!(str = malloc(ft_strclen(s + *i, c) + 1)))
		return (NULL);
	k = 0;
	while (s[*i] != c && s[*i])
	{
		str[k] = s[*i];
		k++;
		*i += 1;
	}
	str[k] = '\0';
	while (s[*i] == c && s[*i])
		*i += 1;
	return (str);
}

static int	ft_countword(const char *str, char c)
{
	int i;
	int number_of_words;

	i = 0;
	number_of_words = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			number_of_words++;
			while (str[i] != c && str[i])
				i++;
		}
		else
			i++;
	}
	return (number_of_words);
}

char	**ft_strsplit(const char *s, char c)
{
	int		i;
	int		j;
	char	**result;
	int		num_words;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	num_words = ft_countword(s, c);
	if (num_words == 0)
		return (NULL);
	if (!(result = (char**)malloc(sizeof(char*) * (num_words + 2))))
		return (NULL);
	while (s[i] == c && s[i])
		i++;
	while (j < num_words && s[i])
	{
		result[j] = ft_getword((char*)s, c, &i);
		j++;
	}
	result[j] = NULL;
	return (result);
}
