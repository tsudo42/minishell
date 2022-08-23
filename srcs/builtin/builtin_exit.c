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
	return (exit_status);//change this
}

int	builtin_exit(char **argv)
{
	int	exit_status;

	if (argv[1] == NULL)
		exit (0); // check this
	if (argv[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (STATUS_FAILURE);// has to return 1
	}
	if ((exit_status = get_exit_status(argv[1])) == -1)
	{
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		exit (255);
	}
	exit(exit_status); //change this
}
