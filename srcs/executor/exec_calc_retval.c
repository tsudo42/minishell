/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_calc_retval.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include <sys/wait.h>

int	exec_calc_retval(int stat)
{
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	if (WIFSIGNALED(stat))
		return (WTERMSIG(stat) + 128);
	return (WSTOPSIG(stat) + 128);
}
