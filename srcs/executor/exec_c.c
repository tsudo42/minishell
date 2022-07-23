/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include <stdlib.h>
#include <stdio.h>

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
	pid_t	pid;
	int		ret_val;
	char	*path;

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
	if (waitpid(pid, &ret_val, 0) < 0)
	{
		perror(EXEC_ERRMSG ": waitpid");
		errno = 0;
		ret_val = 1;
	}
	return (ret_val);
}

int	exec_c(t_ast_c *c)
{
	char	**args;
	int		(*builtin_func)(char **);

	if (c == NULL)
		exec_error("c is NULL");
	args = exec_a(c->a);
	if (args == NULL)
		exec_error("args is NULL");
	if (args[0] != NULL)
		builtin_func = get_builtin_func(args[0]);
	else
		builtin_func = NULL;
	if (builtin_func != NULL)
		return (exec_c_builtin(builtin_func, args, c->d));
	return (exec_c_command(args, c->d));
}

void	ast_free_c(t_ast_c *c)
{
	if (c == NULL)
		return ;
	ast_free_a(c->a);
	ast_free_d(c->d);
	free(c);
}
