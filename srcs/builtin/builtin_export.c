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

static int	print_contents(void)
{
	t_env	**env;
	t_env	*tmp_env;

	env = ft_getenv(();
	tmp_env = *env;
	while (tmp_env != NULL)
	{
		printf("%s=\"%s\"\n", tmp_env->env_var, tmp_env->content);
/*
		ft_putstr_fd(tmp_env->env_var, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(tmp_env->content, STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
		tmp_env = tmp_env->next;
*/
	}
	return (STATUS_SUCCESS);
}

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
			printf("export: '%s", *argv);
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

int main(void)
{
	char *argv[10];
	char str[10] = "export";
	//	char str1[10] = "-n";
	char str1[10] = "TEST=\"test\"";
	char str2[10] = "TEST2=\"test2\"";
	char str3[10] = "TEST3=\"test3\"";
	char *str4;

	str4 = NULL;
	argv[0] = str;
	argv[1] = str1;
	argv[2] = str2;
	argv[3] = str3;
	argv[4] = str4;
	builtin_export(argv);
	return (0);
}
