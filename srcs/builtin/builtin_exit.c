/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/12 15:31:16 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static long	builtin_get_exit_status(char *str)
{
	long	num;
	char	*endptr;

	errno = 0;
	num = ft_strtol(str, &endptr, 10);
	if (errno || *endptr != '\0')
		return (-1);
	return (num);
}

static void	builtin_put_msg_and_exit(char *str, char *argv, int status)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (str)
	{
		ft_putstr_fd(EXIT_ERRMSG, STDERR_FILENO);
		if (argv)
		{
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(argv, STDERR_FILENO);
		}
		ft_putstr_fd(str, STDERR_FILENO);
	}
	exit (status);
}

int	builtin_exit(char **argv, t_environ *env)
{
	long	exit_status;

	if (argv == NULL || *argv == NULL)
		return (STATUS_FAILURE);
	(void)env;
	if (argv[1] == NULL)
		builtin_put_msg_and_exit(NULL, NULL, 0);
	exit_status = builtin_get_exit_status(argv[1]);
	if (exit_status == -1)
		builtin_put_msg_and_exit(": numeric argument required\n", \
			argv[1], 255);
	if (argv[2] != NULL)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd(EXIT_ERRMSG ": too many arguments\n", STDERR_FILENO);
		return (1);
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit (exit_status);
}
