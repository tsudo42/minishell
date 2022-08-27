/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 11:39:06 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	builtin_get_exit_status(char *str)
{
	int	exit_status;

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
	return (exit_status);
}

int	builtin_exit(char **argv)
{
	int	exit_status;

	if (argv[1] == NULL)
		exit (0);
	if (argv[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	exit_status = builtin_get_exit_status(argv[1]);
	if (exit_status == -1)
	{
		ft_putstr_fd("exit: a numeric argument required\n", STDERR_FILENO);
		exit (255);
	}
	exit(exit_status);
}
