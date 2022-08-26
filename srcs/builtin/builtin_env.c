/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/26 17:50:50 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_env(char **argv)
{
	extern char	**environ;
	int			i;

	(void)argv;
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "LINES=", 6) == 0)
		{
			i++;
			continue ;
		}
		else if (ft_strncmp(environ[i], "COLUMNS=", 8) == 0)
		{
			i++;
			continue ;
		}
		ft_putstr_fd(environ[i++], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (STATUS_SUCCESS);
}
