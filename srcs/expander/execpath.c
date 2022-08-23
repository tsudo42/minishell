/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "environ.h"
#include "libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	**get_path_env(void)
{
	char	*path_env_raw;

	path_env_raw = ft_getenv("PATH");
	if (path_env_raw == NULL)
		return (NULL);
	return (ft_split_sep(path_env_raw, ":"));
}

void	terminate_path_env(char **path_env)
{
	char	**path_env_head;

	if (path_env == NULL)
		return ;
	path_env_head = path_env;
	while (*path_env != NULL)
	{
		free(*path_env);
		path_env++;
	}
	free(path_env_head);
}

char	*execpath_from_env(char *name, char **path_env)
{
	char	*exec_path;

	if (path_env == NULL)
		return (NULL);
	exec_path = NULL;
	while (*path_env != NULL)
	{
		if (**path_env == '\0')
			exec_path = ft_strdup(name);
		else
			exec_path = ft_strjoin3(*path_env, "/", name);
		if (exec_path == NULL)
		{
			perror(EXPANDER_ERRMSG ": malloc");
			return (NULL);
		}
		if (access(exec_path, X_OK) == 0 || \
			access(exec_path, R_OK | X_OK) == 0)
			break ;
		ft_free_set((void **)&exec_path, NULL);
		path_env++;
	}
	return (exec_path);
}

char	*execpath(char *name)
{
	char	*exec_path;
	char	**path_env;

	errno = 0;
	if (name == NULL)
		exec_path = ft_strdup("");
	else if (ft_strchr(name, '/') != NULL)
		exec_path = ft_strdup(name);
	else
	{
		exec_path = NULL;
		path_env = get_path_env();
		if (path_env != NULL)
			exec_path = execpath_from_env(name, path_env);
		if (exec_path == NULL)
			exec_path = ft_strdup(name);
		terminate_path_env(path_env);
	}
	if (exec_path == NULL)
		perror(EXPANDER_ERRMSG ": malloc");
	errno = 0;
	return (exec_path);
}
