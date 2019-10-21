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