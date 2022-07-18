#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <errno.h>


char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != (char)c && s[i] != '\0')
		i++;
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	if ((unsigned char)s1[i] == (unsigned char)s2[i])
		return (0);
	else if ((unsigned char)s1[i] > (unsigned char)s2[i])
		return (1);
	else
		return (-1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
