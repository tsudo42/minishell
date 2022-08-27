/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_internal_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include <stdlib.h>
#include <unistd.h>

void	exec_error(const char *name)
{
	ft_putstr_fd(EXEC_INTERNAL_ERRMSG ": ", STDERR_FILENO);
	ft_putendl_fd(name, STDERR_FILENO);
	exit(EXEC_INTERNAL_ERRNUM);
}
