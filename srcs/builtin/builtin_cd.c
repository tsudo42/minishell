/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/31 15:50:01 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	cd_to_home(t_environ *env)
{
	char	*home_dir;

	home_dir = variable_get("HOME", env);
	if (home_dir == NULL)
	{
		ft_putendl_fd(CD_ERRMSG ": No Home", STDERR_FILENO);
		return (STATUS_FAILURE);
	}
	if (chdir(home_dir) == -1)
	{
		perror(CD_ERRMSG ": chdir");
		return (STATUS_FAILURE);
	}
	return (STATUS_SUCCESS);
}

int	builtin_cd(char **argv, t_environ *env)
{
	if (argv[1] == NULL)
		return (cd_to_home(env));
	if (chdir(argv[1]) == -1)
	{
		perror(CD_ERRMSG ": chdir");
		return (STATUS_FAILURE);
	}
	return (STATUS_SUCCESS);
}
