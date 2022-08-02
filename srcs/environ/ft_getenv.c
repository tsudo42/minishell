/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
			return (-1);
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			break ;
		s1++;
		s2++;
		if (!s1 || !s2)
			return (-1);
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_getenv(const char *name)
{
	extern char	**environ;
	char	**tmp;
	char	*content;
	int		len;

	if (ft_strcmp("?", name) == 0)
		return (ft_itoa(g_status));
	if (!name)
		return (NULL);
	tmp = environ;
	len = ft_strlen(name);
	while (*tmp)
	{
		if (ft_strncmp(*tmp, name, len) == 0)
		{
			content = ft_strchr(*tmp, '=');
			content++;
			return (ft_strdup(content));
		}
		tmp++;
	}
	return (NULL);
}

/*tester
int main(void)
{
	char *env;
	extern char **environ;
	char **tmp = environ;

	env = ft_getenv("HOME");
	printf("HOME=%s\n", env);
	free (env);
	ft_putenv("USER");
	printf("\n");
	ft_setenv("TEST", "test", 1);
	(void)tmp;
	env = ft_getenv("TEST");
	printf("TEST=%s\n", env);
	free (env);
	ft_unsetenv("TEST");
	printf("TEST=%s\n", env);
	env = ft_getenv("TEST");
	printf("TEST=%s\n", env);
	free (env);
	return (0);
}
*/
