/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int get_exit_status(char *str)
{
	int exit_status;

	exit_status = 0;
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (-1);
		str++;
	}
	exit_status = ft_atoi(str);
	if (256 <= exit_status)
		exit_status = exit_status % 256; 
	else if (exit_status < 0)
		exit_status = 0;
//		exit_status = exit_status 
return (exit_status);
}

int	builtin_exit(char **argv)
{
	int	exit_status;

	if (argv[1] == NULL)
		exit (g_status);
	if (argv[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (STATUS_FAILURE);// has to reaturn 1
	}
	if ((exit_status = get_exit_status(argv[1])) == -1)
	{
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		exit (255);
	}
	exit(exit_status);
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
	builtin_exit(argv);
	return (0);
}
