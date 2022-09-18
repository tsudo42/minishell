/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/15 15:34:59 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>

int	set_pwd(t_environ *env)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		perror(CD_ERRMSG ": getcwd");
		return (BUILTIN_FAILURE);
	}
	variable_set("OLDPWD", variable_get("PWD", env), 0, env);
	variable_set("PWD", buf, 0, env);
	return (BUILTIN_SUCCESS);
}

int	builtin_cd(char **argv, t_environ *env)
{
	char	*dest;

	if (argv == NULL || *argv == NULL)
		return (STATUS_FAILURE);
	if (argv[1] != NULL)
		dest = argv[1];
	else
	{
		dest = variable_get("HOME", env);
		if (dest == NULL)
		{
			ft_dprintf(STDERR_FILENO, "%s: HOME not set\n", CD_ERRMSG);
			return (STATUS_FAILURE);
		}
	}
	if (chdir(dest) == -1)
	{
		ft_dprintf(STDERR_FILENO, \
			"%s: %s: %s\n", CD_ERRMSG, dest, strerror(errno));
		return (STATUS_FAILURE);
	}
	return (set_pwd(env));
}
