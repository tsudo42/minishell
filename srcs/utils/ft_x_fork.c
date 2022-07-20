/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* ************************************************************************** */
/*  This function is an error checking version of fork(2).                    */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when fork faces error.                                            */
/* ************************************************************************** */
pid_t	ft_x_fork(const char *errmsg)
{
	pid_t	ret;

	ret = fork();
	if (ret >= 0)
		return (ret);
	perror(errmsg);
	exit(INTERNAL_ERR_NUM);
}
