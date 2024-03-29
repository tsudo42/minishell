/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 17:15:34 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>
#include <stdlib.h>

int	builtin_pwd(char **argv, t_environ *env)
{
	char	*path;

	(void)env;
	(void)argv;
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror(PWD_ERRMSG ": getcwd");
		return (BUILTIN_FAILURE);
	}
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (BUILTIN_SUCCESS);
}
