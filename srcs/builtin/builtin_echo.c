/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 17:15:34 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_internal.h"

int	builtin_echo(char **argv)
{
	bool	print_newline;

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
