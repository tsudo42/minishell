/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/04 09:10:57 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>

static int	(*get_builtin_func(char	*name))(char **args, t_environ *env)
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

static int	exec_c_builtin(int (*builtin_func)(char **, t_environ *), \
	char **args, t_ast_d *d, t_environ *env)
{
	int	stdfds[3];
	int	ret;

	exec_stdfd_set(stdfds);
	if (exec_d(d, env) != 0)
	{
		exec_stdfd_reset(stdfds);
		return (1);
	}
	ret = builtin_func(args, env);
	exec_stdfd_reset(stdfds);
	return (ret);
}

static void	exec_c_command_child(char **args, char **envp, t_environ *env)
{
	char		*path;
	struct stat	st;
	int			exec_errno;
	const char	*errmsg;

	if (args[0] == NULL)
		exit(0);
	path = execpath(args[0], env);
	if (path == NULL && errno == ENOENT)
		exit(127);
	else if (path == NULL)
		exit(2);
	ready_exec_signal();
	execve(path, args, envp);
	exec_errno = errno;
	if (stat(path, &st) == 0 && (st.st_mode & S_IFMT) == S_IFDIR)
		errmsg = "is a directory";
	else
		errmsg = strerror(exec_errno);
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", EXEC_ERRMSG, path, errmsg);
	exit(126);
}

static int	exec_c_command(char **args, t_ast_d *d, t_environ *env)
{
	pid_t	pid;
	int		stat;
	int		fifo[2];

	ft_x_pipe(fifo, EXEC_ERRMSG ": pipe");
	pid = ft_x_fork(EXEC_ERRMSG);
	if (pid == 0)
	{
		env->my_pid = exec_pid_recv(fifo);
		if (exec_d(d, env) != 0)
			exit(1);
		exec_c_command_child(args, generate_envp(env), env);
	}
	exec_pid_tell(fifo, pid);
	if (waitpid(pid, &stat, WUNTRACED) < 0)
	{
		perror(EXEC_ERRMSG ": waitpid");
		errno = 0;
		return (1);
	}
	return (exec_calc_retval(stat, env));
}

int	exec_c(t_ast_c *c, t_environ *env)
{
	char	**args;
	int		(*builtin_func)(char **, t_environ *env);
	int		ret;

	if (c == NULL)
		exec_error("c is NULL");
	args = exec_a(c->a, env);
	if (args == NULL)
	{
		env->exit_status = 1;
		return (1);
	}
	if (args[0] != NULL)
		builtin_func = get_builtin_func(args[0]);
	else
		builtin_func = NULL;
	if (builtin_func != NULL)
		ret = exec_c_builtin(builtin_func, args, c->d, env);
	else
		ret = exec_c_command(args, c->d, env);
	ft_free_strarr(args);
	env->exit_status = ret;
	return (ret);
}
