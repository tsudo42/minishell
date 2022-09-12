/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/12 16:52:35 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	cd_to_home(t_environ *env)
{
	char	*home_dir;
	char	buf[PATH_MAX];

	home_dir = variable_get("HOME", env);
	if (home_dir == NULL)
	{
		ft_putendl_fd(CD_ERRMSG ": No Home", STDERR_FILENO);
		return (STATUS_FAILURE);
	}
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		perror(CD_ERRMSG ": getcwd");
		return (STATUS_FAILURE);
	}
	if (variable_get("OLDPWD"))
		variable_set("OLDPWD", buf, 1, env);
	if (chdir(home_dir) == -1)
	{
		perror(CD_ERRMSG ": chdir");
		return (STATUS_FAILURE);
	}
	if (variable_get("PWD"))
		variable_set("PWD", buf, 0, env);
	return (STATUS_SUCCESS);
}

int	builtin_cd(char **argv, t_environ *env)
{
	char	buf[PATH_MAX];

	if (argv == NULL || *argv == NULL)
		return (STATUS_FAILURE);
	if (argv[1] == NULL)
		return (cd_to_home(env));
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		perror(CD_ERRMSG ": getcwd");
		return (STATUS_FAILURE);
	}
	if (variable_get("OLDPWD"))
		variable_set("OLDPWD", buf, 1, env);
	if (chdir(argv[1]) == -1)
	{
		perror(CD_ERRMSG ": chdir");
		return (STATUS_FAILURE);
	}
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		perror(CD_ERRMSG ": getcwd");
		return (STATUS_FAILURE);
	}
	if (variable_get("PWD"))
		variable_set("PWD", buf, 0, env);
	return (STATUS_SUCCESS);
}
