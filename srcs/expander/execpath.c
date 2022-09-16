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
#include <sys/stat.h>
#include <unistd.h>

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

static int	is_valid_command(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (0);
	if ((st.st_mode & S_IFMT) == S_IFDIR)
		return (0);
	if (access(path, X_OK) != 0 && access(path, R_OK | X_OK) != 0)
		return (0);
	return (1);
}

char	*execpath_from_env(char *name, char **path_env)
{
	char	*exec_path;

	exec_path = NULL;
	while (*path_env != NULL)
	{
		errno = 0;
		if (**path_env == '\0')
			exec_path = ft_strjoin("./", name);
		else
			exec_path = ft_strjoin3(*path_env, "/", name);
		if (exec_path == NULL)
		{
			perror(EXPANDER_ERRMSG ": malloc");
			return (NULL);
		}
		if (is_valid_command(exec_path))
			return (exec_path);
		ft_free_set((void **)&exec_path, NULL);
		path_env++;
	}
	errno = ENOENT;
	ft_dprintf(STDERR_FILENO, \
		"%s: %s: command not found\n", EXPANDER_ERRMSG, name);
	return (exec_path);
}

char	*execpath(char *name, t_environ *env)
{
	char	*exec_path;
	char	*path_env;
	char	**path_list;

	path_env = variable_get("PATH", env);
	if (name == NULL)
		exec_path = ft_strdup("");
	else if (ft_strchr(name, '/') != NULL || path_env == NULL)
		exec_path = ft_strdup(name);
	else
	{
		path_list = ft_split_sep(path_env, ":");
		if (path_list == NULL)
		{
			perror(EXPANDER_ERRMSG ": malloc");
			return (NULL);
		}
		exec_path = execpath_from_env(name, path_list);
		terminate_path_env(path_list);
		return (exec_path);
	}
	if (exec_path == NULL)
		perror(EXPANDER_ERRMSG ": malloc");
	return (exec_path);
}
