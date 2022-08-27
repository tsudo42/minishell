/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 16:52:06 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static int	envdup_unset(char **new_env, int skip)
{
	extern char	**environ;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (environ[j])
	{
		if (j == skip)
			j++;
		if (environ[j] != NULL)
		{
			new_env[i] = ft_strdup(environ[j++]);
			if (!new_env[i++])
			{
				free_environ();
				return (-1);
			}
		}
	}
	new_env[i] = NULL;
	return (0);
}

static char	**del_one_environ(int skip)
{
	extern char	**environ;
	char		**new_env;

	if (!environ)
		return (NULL);
	new_env = (char **)malloc(sizeof(char *) * (envlen(environ)));
	if (!new_env)
	{
		free_environ();
		return (NULL);
	}
	if (envdup_unset(new_env, skip) == -1)
	{
		free_environ();
		return (NULL);
	}
	free_environ();
	environ = NULL;
	return (new_env);
}

int	ft_unsetenv(const char *name)
{
	extern char	**environ;
	int			skip;

	skip = find_name(name);
	if (skip == -1)
		return (0);
	environ = del_one_environ(skip);
	if (!environ)
		ft_perror_exit(EXIT_FAILURE, ENVIRON_ERRMSG ": malloc");
	return (0);
}
