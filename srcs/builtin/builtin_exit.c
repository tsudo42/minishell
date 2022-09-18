/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/15 15:09:29 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdlib.h>

static long	builtin_get_exit_status(char *str)
{
	long	num;
	char	*endptr;

	errno = 0;
	num = ft_strtol(str, &endptr, 10);
	while (ft_isspace(*endptr))
		endptr++;
	if (*endptr != '\0' || errno != 0)
		return (-1);
	return (num);
}

int	builtin_exit(char **argv, t_environ *env)
{
	long	exit_status;

	if (argv == NULL || *argv == NULL)
		return (BUILTIN_FAILURE);
	(void)env;
	if (argv[1] == NULL)
	{
		ft_dprintf(STDERR_FILENO, "exit\n");
		exit (env->exit_status);
	}
	exit_status = builtin_get_exit_status(argv[1]);
	if (exit_status == -1)
	{
		ft_dprintf(STDERR_FILENO, \
			"exit\n%s: %s: numeric argument required\n", EXIT_ERRMSG, argv[1]);
		exit (255);
	}
	if (argv[2] != NULL)
	{
		ft_dprintf(STDERR_FILENO, "exit\n%s: too many arguments\n", EXIT_ERRMSG);
		return (1);
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit (exit_status);
}
