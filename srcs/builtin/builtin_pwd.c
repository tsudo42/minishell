/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(char **argv)
{
	char	*path;

	(void)argv;
	if ((path = getcwd(NULL, 0)) == NULL)
		return (STATUS_FAILURE);
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (STATUS_SUCCESS);
}
