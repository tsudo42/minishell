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

#include "builtin.h"

static int	is_option_n(char *str)
{
	size_t	i;

	if (str == NULL || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(char **argv, t_environ *env)
{
	bool	print_newline;

	if (argv == NULL || *argv == NULL)
		return (STATUS_FAILURE);
	(void)env;
	argv++;
	print_newline = !is_option_n(*argv);
	while (is_option_n(*argv))
		argv++;
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
