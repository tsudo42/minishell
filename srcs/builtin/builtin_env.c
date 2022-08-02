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
	extern char **environ;
	int i;

	(void)argv;
	i = 0;
//	ft_init_environ();
	while (environ[i])
	{
		ft_putstr_fd(environ[i++], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (STATUS_SUCCESS);
}
/*
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

*/

