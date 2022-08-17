/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static char **del_one_environ(int skip)
{
	extern char **environ;
	char	**env_new;
	int i;
	int j;

	env_new = (char **)malloc(sizeof(char *) * (envlen()));
	if (!env_new)
	{
		free_environ();
		perror("add_environ");
		exit(EXIT_FAILURE);
	}
	if (!environ)
		return NULL;
	i = 0;
	j = 0;
	while (environ[j])
	{
		if (j == skip)
			j++;
		if (environ[j] != NULL)
			env_new[i++] = ft_strdup(environ[j++]);
	}
//	env_new[i] = ft_strdup("");
	env_new[i] = NULL;
	free_environ();
	environ = NULL;
	return (env_new);
}

int	ft_unsetenv(const char *name)
{
	extern char **environ;
//	char **env_new;
	int skip;

	init_environ();
	if ((skip = find_name(name)) == -1)
		return (0);
//	env_new = del_one_environ(skip);
	environ = del_one_environ(skip);
//	if (!environ)
//		return (-1);
//	free (environ);
//	environ = env_new;
	return (0);
}
