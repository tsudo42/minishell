/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_env(char **argv)
{
	t_env		**env;
	t_env		*tmp_env;

	(void)argv;
	env = ft_getenv();
	tmp_env = *env;
	while (tmp_env != NULL)
	{
		ft_putstr_fd(tmp_env->env_var, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(tmp_env->content, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		tmp_env = tmp_env->next;
	}
	return (STATUS_SUCCESS);
}

int main(void)
{
	char *argv[10];
	char str[10] = "echo";
	//	char str1[10] = "-n";
	char str1[10] = "str1";
	char str2[10] = "str2";
	char str3[10] = "str3";
	char *str4;

	str4 = NULL;
	argv[0] = str;
	argv[1] = str1;
	argv[2] = str2;
	argv[3] = str3;
	argv[4] = str4;
	builtin_env(argv);
	return (0);
}
