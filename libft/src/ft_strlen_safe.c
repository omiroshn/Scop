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
