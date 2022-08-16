/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	cd_to_home(void)
{
	char	*home_dir;

	home_dir = ft_getenv("HOME");
	if (home_dir == NULL)
	{
		perror("cd_to_home");
		return (STATUS_FAILURE);
	}
	if (chdir(home_dir) == -1)
	{
		free(home_dir);
		perror("cd_to_home2");
		return (STATUS_FAILURE);
	}
//	free(home_dir);
	return (STATUS_SUCCESS);
}

int	builtin_cd(char **argv)
{
	if (argv[1] == NULL)
		return (cd_to_home());
	if (chdir(argv[1]) == -1)
	{
		perror("builtin_cd");
		return (STATUS_FAILURE);
	}
	return (STATUS_SUCCESS);
}
