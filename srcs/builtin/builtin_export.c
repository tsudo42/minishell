/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void ft_putstrlen_fd(const char *s, size_t len, int fd)
{
	size_t i;

	if (s == NULL)
	{
		write(fd, "(null)", 6);
		return ;
	}
	i = 0;
	while (s[i] != '\0' && i < len) 
	 	i++;
	if (i != 0)
		write(fd, s, i);
}

static int	print_contents(void)
{
	extern char	**environ;
	int i;
	char *str;
	char *content;

	//ft_init_environ();
	i = 0;
	while (environ[i])
	{
		if (environ[i][0] == '_')
		{
			i++;
			continue ;
		}
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		str = ft_strdup(environ[i++]);
		content = ft_strchr(str, '=');
		ft_putstrlen_fd(str, content - str, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(++content, STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
	}
	return (STATUS_SUCCESS);
}

//add the function to check if the parameter is valid or not.


static int	export_contents(char **argv)
{
	char	*env_var;
	char	*content;
	int		status;

	status = STATUS_SUCCESS;
	while (*(++argv) != NULL)
	{
		env_var = ft_strdup(*argv);
		content = ft_strchr(env_var, '=');
		if (!ft_isalpha(env_var[0]))
		{
			status = STATUS_FAILURE;
			printf("export: '%s", *argv); // has to change this to ft_putstr?
			ft_putstr_fd("': not a valid identifier", STDERR_FILENO);
			free(env_var);
			continue;
		}
		if (content != NULL)
		{
			*content = '\0';
			ft_setenv(env_var, ++content, 0); // change the 3rd argument later
		}
		free (env_var);
	}
	return (status);
}

int	builtin_export(char **argv)
{
	if (argv[1] == NULL)
		return (print_contents());
	else
		return (export_contents(argv));
}

/*
int main(void)
{
	char *argv[10];
	char str[10] = "export";
	//	char str1[10] = "-n";
	char str1[15] = "TEST=test";
	char str2[15] = "TEST2=test2";
	char str3[15] = "TEST3=test3";
	char *str4;

	str4 = NULL;
	argv[0] = str;
	argv[1] = str1;
	argv[2] = str2;
	argv[3] = str3;
	argv[4] = str4;
	builtin_export(argv);
//	ft_putenv("TEST2");
	builtin_env(argv);
	printf("\n\n");

	char *xargv[10];
	char xstr[10] = "AAA";
	//	char str1[10] = "-n";
	char xstr1[15] = "TEST";
	char xstr2[15] = "TEST2";
	char xstr3[15] = "TEST3";
	char *xstr4;

	xstr4 = NULL;
	xargv[0] = xstr;
	xargv[1] = xstr1;
	xargv[2] = xstr2;
	xargv[3] = xstr3;
	xargv[4] = xstr4;
	builtin_unset(xargv);
	argv[1] = NULL;
	argv[2] = NULL;
	argv[3] = NULL;

	builtin_env(xargv);
	//	builtin_export(argv);
	return (0);
}
*/
