/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/04 13:42:30 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_internal.h"

static int	find_name(const char *name)
{
	extern char	**environ;
	int			i;
	size_t		len;
	size_t		len_env;

	if (!environ)
		return (-1);
	i = 0;
	len = ft_strlen(name);
	while (environ[i])
	{
		len_env = ft_strlen(environ[i]);
		if (len_env < len)
		{
			i++;
			continue ;
		}
		if (ft_strncmp(environ[i], name, len) == 0 \
			&& environ[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static int	envdup_unset(char **new_env, int location)
{
	extern char	**environ;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (environ[j])
	{
		if (j == location)
			j++;
		if (environ[j] != NULL)
			new_env[i++] = ft_x_strdup(environ[j++], ENVIRON_ERRMSG);
	}
	new_env[i] = NULL;
	return (0);
}

static char	**del_one_environ(long location)
{
	extern char	**environ;
	char		**new_env;

	if (!environ)
		return (NULL);
	new_env = (char **)ft_x_malloc(sizeof(char *) * (envlen(environ)), \
		ENVIRON_ERRMSG ": malloc");
	envdup_unset(new_env, location);
	free_environ();
	is_init_environ(1);
	return (new_env);
}

int	ft_unsetenv(const char *name)
{
	extern char	**environ;
	int			location;

	location = find_name(name);
	if (location == -1)
		return (0);
	environ = del_one_environ(location);
	return (0);
}
