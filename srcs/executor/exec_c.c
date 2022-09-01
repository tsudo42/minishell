/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/26 18:14:14 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

static int	(*get_builtin_func(char	*name))(char **args)
{
	if (ft_strncmp("echo", name, sizeof("echo")) == 0)
		return (builtin_echo);
	if (ft_strncmp("cd", name, sizeof("cd")) == 0)
		return (builtin_cd);
	if (ft_strncmp("pwd", name, sizeof("pwd")) == 0)
		return (builtin_pwd);
	if (ft_strncmp("export", name, sizeof("export")) == 0)
		return (builtin_export);
	if (ft_strncmp("unset", name, sizeof("unset")) == 0)
		return (builtin_unset);
	if (ft_strncmp("env", name, sizeof("env")) == 0)
		return (builtin_env);
	if (ft_strncmp("exit", name, sizeof("exit")) == 0)
		return (builtin_exit);
	return (NULL);
}

static int	exec_c_builtin(\
	int (*builtin_func)(char **), char **args, t_ast_d *d)
{
	int	stdfds[3];
	int	ret;

	exec_stdfd_set(stdfds);
	if (exec_d(d) != 0)
	{
		exec_stdfd_reset(stdfds);
		return (1);
	}
	ret = builtin_func(args);
	exec_stdfd_reset(stdfds);
	return (ret);
}

static int	exec_c_command(char **args, t_ast_d *d)
{
	pid_t		pid;
	int			stat;
	char		*path;
	extern char	**environ;

	path = execpath(args[0]);
	if (path == NULL)
		exec_error("execpath");
	pid = ft_x_fork(EXEC_ERRMSG);
	if (pid == 0)
	{
		if (exec_d(d) != 0)
			exit(1);
		if (*path == '\0')
			exit(0);
		ft_x_execve(path, args, environ, EXEC_ERRMSG);
	}
	free(path);
	if (waitpid(pid, &stat, 0) < 0)
	{
		perror(EXEC_ERRMSG ": waitpid");
		errno = 0;
		return (1);
	}
	return (exec_calc_retval(stat));
}

int	exec_c(t_ast_c *c)
{
	char	**args;
	int		(*builtin_func)(char **);
	int		ret;

	if (c == NULL)
		exec_error("c is NULL");
	args = exec_a(c->a);
	if (args == NULL)
	{
		set_exit_status(1);
		return (1);
	}
	if (args[0] != NULL)
		builtin_func = get_builtin_func(args[0]);
	else
		builtin_func = NULL;
	if (builtin_func != NULL)
		ret = exec_c_builtin(builtin_func, args, c->d);
	else
		ret = exec_c_command(args, c->d);
	ft_free_strarr(args);
	set_exit_status(ret);
	return (ret);
}
