/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_waitpid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

/* ************************************************************************** */
/*  This function is an error checking version of waitpid(2).                 */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when waitpid faces error.                                         */
/* ************************************************************************** */
pid_t	ft_x_waitpid(pid_t pid, int *stat_loc, int opitons, const char *errmsg)
{
	pid_t	ret;

	ret = waitpid(pid, stat_loc, opitons);
	if (ret >= 0)
		return (ret);
	perror(errmsg);
	exit(INTERNAL_ERR_NUM);
}
