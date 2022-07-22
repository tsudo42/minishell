int ft_builtin_echo(char *const argv[], char *const envp[]);
int ft_builtin_cd(char *const argv[], char *const envp[]);
int ft_builtin_pwd(char *const argv[], char *const envp[]);
int ft_builtin_export(char *const argv[], char *const envp[]);
int ft_builtin_unset(char *const argv[], char *const envp[]);
int ft_builtin_env(char *const argv[], char *const envp[]);
int ft_builtin_exit(char *const argv[], char *const envp[]);

bool	ft_is_builtin(char *cmd)
{
	return (ft_strcmp("cd", cmd) == 0
			|| ft_strcmp("echo", cmd) == 0
			|| ft_strcmp("env", cmd) == 0
			|| ft_strcmp("exit", cmd) == 0
			|| ft_strcmp("export", cmd) == 0
			|| ft_strcmp("pwd", cmd) == 0
			|| ft_strcmp("unset", cmd) == 0);
}

int	ft_exec_builtin(char **argv, char *const envp[])
{
	if (ft_strcmp("cd", argv[0]) == 0)
		return ft_(builtin_cd(argv)); // change the argument
	if (ft_strcmp("echo", argv[0]) == 0)
		return (ft_builtin_echo(argv));
	if (ft_strcmp("env", argv[0]) == 0)
		return (ft_builtin_env(argv));
	if (ft_strcmp("exit", argv[0]) == 0)
		return (ft_builtin_exit(argv));
	if (ft_strcmp("export", argv[0]) == 0)
		return (ft_builtin_export(argv));
	if (ft_strcmp("pwd", argv[0]) == 0)
		return (ft_builtin_pwd(argv));
	if (ft_strcmp("unset", argv[0]) == 0)
		return (ft_builtin_unset(argv));
	return (1);
}




/*
int	ft_exec_a_builtin(t_exec_info	*info)
{
	int	save_stdout;
	int	save_stdin;
	int	exit_status;
	int	tmp_fd;

	save_stdout = STDOUT_FILENO;
	save_stdin = STDIN_FILENO;
	if (info->dstfile != NULL)
	{
		save_stdout = xdup(STDOUT_FILENO);
		tmp_fd = xopen(info->dstfile, O_RDWR | O_CREAT, 0644);
		replace_fd(tmp_fd, STDOUT_FILENO);
	}
	if (info->srcfile != NULL)
	{
		save_stdout = xdup(STDIN_FILENO);
		tmp_fd = xopen(info->srcfile, O_RDONLY, 0);
		replace_fd(tmp_fd, STDIN_FILENO);
	}
	exit_status = execute_builtin(info->cmds[0]);
	replace_fd(save_stdout, STDOUT_FILENO);
	replace_fd(save_stdin, STDIN_FILENO);
	return (exit_status);
}
*/
