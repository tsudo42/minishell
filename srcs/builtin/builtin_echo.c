/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/12 08:30:50 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_echo(char **argv, t_environ *env)
{
	bool	print_newline;

	if (argv == NULL || *argv == NULL)
		return (STATUS_FAILURE);
	(void)env;
	print_newline = true;
	argv++;
	if (*argv != NULL && ft_strncmp("-n", *argv, 3) == 0)
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
