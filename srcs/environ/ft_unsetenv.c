/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/25 13:06:49 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static void free_env_new(char **env_new, int i)
{
	int j;

	j = 0;
	if (!env_new)
		return ;
	while(j < i - 2)
		free(env_new[j++]);
	free (env_new);
	return ;
}

static int envdup_unset(char **env_new, int skip)
{
	extern char **environ;
	int i;
	int j;

	i = 0;
	j = 0;
	while (environ[j])
	{
		if (j == skip)
			j++;
		if (environ[j] != NULL)
		{
			env_new[i] = ft_strdup(environ[j++]);
			if (!env_new[i++])
			{
				free_env_new(env_new, i);
				return (-1);
			}
		}
	}
	env_new[i] = NULL;
	return (0);
}

static char **del_one_environ(int skip)
{
	extern char **environ;
	char	**env_new;

	if (!environ)
		return (NULL);
	env_new = (char **)malloc(sizeof(char *) * (envlen()));
	if (!env_new)
	{
		free_environ();
		return (NULL);
	}
	if (envdup_unset(env_new, skip) == -1)
	{
		free_environ();
		return (NULL);
	}
	free_environ();
	environ = NULL;
	return (env_new);
}

int	ft_unsetenv(const char *name)
{
	extern char **environ;
	int skip;

//	init_environ();
	if ((skip = find_name(name)) == -1)
		return (0);
	environ = del_one_environ(skip);
	if (!environ)
		ft_perror_exit(EXIT_FAILURE, ENV_ERRMSG ": malloc");
	return (0);
}
