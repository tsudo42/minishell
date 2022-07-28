/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_echo(char **argv)
{
	bool	print_newline;

	print_newline = true;
	argv++;
	if (*argv != NULL && ft_strcmp("-n", *argv) == 0)
	{
		argv++;
		print_newline = false;
	}
	while (*argv != NULL)
	{
		ft_putstr_fd(*argv, STDOUT_FILENO);
		argv++;
		if (*argv != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (print_newline == true)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (STATUS_SUCCESS);
}

int main(void)
{
	char *argv[10];
	char str1[10] = "str1";
	char str2[10] = "str2";
	char str3[10] = "str3";
	char str4[10] = "\0";
	argv[0] = str1;
	argv[1] = str2;
	argv[2] = str3;
	argv[3] = str4;
	builtin_echo(argv);
	return (0);
}
