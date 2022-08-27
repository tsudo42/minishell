/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 17:15:34 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_internal.h"

static int	cd_to_home(void)
{
	char	*home_dir;

	home_dir = ft_getenv("HOME");
	if (home_dir == NULL)
	{
		perror(BUILT_ERRMSG": home_dir");
		return (STATUS_FAILURE);
	}
	if (chdir(home_dir) == -1)
	{
		perror(BUILT_ERRMSG": chdir");
		return (STATUS_FAILURE);
	}
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
