/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/31 15:00:13 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_internal.h"

int	builtin_env(char **argv)
{
	extern char	**environ;
	int			i;

	if (!environ)
		return (STATUS_FAILURE);
	(void)argv;
	i = 0;
	while (environ[i])
	{
		ft_putstr_fd(environ[i++], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (STATUS_SUCCESS);
}
