#include <stdlib.h>

static int	is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*str;

	len = 0;
	while (s1[len])
		len++;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			i;

	if (!s || !(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = -1;
	while (++i < len)
		str[i] = s[start++];
	str[i] = '\0';
	return (str);
}

void	free_strsplit(char **str)
{
	int i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

char		*ft_strtrim(char const *s)
{
	unsigned int	i;
	size_t			len;
	char			*mem;

	if (!s)
		return (0);
	i = 0;
	while (is_whitespace(s[i]))
		++i;
	len = ft_strlen(s) - 1;
	while (len > i && is_whitespace(s[len]))
		len--;
	if (len < i)
		return (mem = ft_strdup(""));
	return (mem = ft_strsub(s, i, len - (size_t)i + 1));
}

static int	ft_word_length(char const *s, char c, unsigned int i)
{
	unsigned int len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		++len;
		++i;
	}
	return (len);
}

int	ft_array_length(char const *s, char c)
{
	unsigned int len;

	len = 0;
	while (*s)
	{
		if (*s == c)
			++s;
		else
		{
			++len;
			while (*s && *s != c)
				++s;
		}
	}
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	char			**ar;
	unsigned int	i;
	unsigned int	j;

	if (!s)
		return (NULL);
	if (!(ar = (char **)malloc(sizeof(char *) * (ft_array_length(s, c) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!(ar[j++] = ft_strsub(s, i, ft_word_length(s, c, i))))
				return (NULL);
			i += ft_word_length(s, c, i);
		}
		else
			i++;
	}
	ar[j] = NULL;
	return (ar);
}