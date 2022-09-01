/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/31 15:06:25 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_internal.h"

static int	builtin_get_exit_status(char *str)
{
	long	num;
	char	*endptr;

	errno = 0;
	num = ft_strtol(str, &endptr, 10);
	if (errno || *endptr != '\0')
		return (-1);
	return (num);
}

int	builtin_exit(char **argv)
{
	int	exit_status;

	free_environ();
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
		return (255);
	}
	exit(exit_status);
}
