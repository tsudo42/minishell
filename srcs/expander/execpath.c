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
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static char	*execpath_without_env(char *name)
{
	struct stat	st;
	char		*exec_path;

	if (stat(name, &st) == 0)
	{
		exec_path = ft_strdup(name);
		if (exec_path == NULL)
			perror(EXPANDER_ERRMSG ": malloc");
		return (exec_path);
	}
	ft_dprintf(STDERR_FILENO, \
		"%s: %s: %s\n", EXPANDER_ERRMSG, name, strerror(ENOENT));
	errno = ENOENT;
	return (NULL);
}

static int	is_valid_command(char **path, char **path_alt)
{
	struct stat	st;

	if (*path == NULL)
	{
		perror(EXPANDER_ERRMSG ": malloc");
		return (2);
	}
	if (stat(*path, &st) != 0)
		return (0);
	if ((st.st_mode & S_IFMT) == S_IFDIR)
		return (0);
	if (access(*path, X_OK) != 0 && access(*path, R_OK | X_OK) != 0)
	{
		if (*path_alt != NULL)
		{
			*path_alt = *path;
			*path = NULL;
		}
		return (0);
	}
	return (1);
}

static char	*execpath_with_env(char *name, char **path_list)
{
	char	*exec_path;
	char	*exec_path_alt;

	exec_path = NULL;
	exec_path_alt = NULL;
	while (*path_list != NULL)
	{
		errno = 0;
		if (**path_list == '\0')
			exec_path = ft_strjoin("./", name);
		else
			exec_path = ft_strjoin3(*path_list, "/", name);
		if (is_valid_command(&exec_path, &exec_path_alt))
			return (exec_path);
		ft_free_set((void **)&exec_path, NULL);
		path_list++;
	}
	ft_dprintf(STDERR_FILENO, \
		"%s: %s: command not found\n", EXPANDER_ERRMSG, name);
	errno = ENOENT;
	return (exec_path);
}

static void	terminate_path_list(char **path_list)
{
	char	**path_list_head;

	if (path_list == NULL)
		return ;
	path_list_head = path_list;
	while (*path_list != NULL)
	{
		free(*path_list);
		path_list++;
	}
	free(path_list_head);
}

/**
 * This function generates full path of executable file searched using PATH
 * environment variable using ft_getenv() and malloc(3).
 * If PATH environment is NULL, name will be ft_strdup-ed.
 *
 * NULL is returned and error message will be printed when:
 * 1). no executable was found (ENOENT).
 * 2). this function encounters malloc(3) error (ENOMEM).
 */
char	*execpath(char *name, t_environ *env)
{
	char	*exec_path;
	char	*path_env;
	char	**path_list;

	if (name == NULL)
	{
		exec_path = ft_strdup("");
		if (exec_path == NULL)
			perror(EXPANDER_ERRMSG ": malloc");
		return (exec_path);
	}
	path_env = variable_get("PATH", env);
	if (*path_env == '\0')
		path_env = NULL;
	if (ft_strchr(name, '/') != NULL || path_env == NULL)
		return (execpath_without_env(name));
	path_list = ft_split_sep(path_env, ":");
	if (path_list == NULL)
	{
		perror(EXPANDER_ERRMSG ": malloc");
		return (NULL);
	}
	exec_path = execpath_with_env(name, path_list);
	terminate_path_list(path_list);
	return (exec_path);
}
