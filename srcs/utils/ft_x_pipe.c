/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* ************************************************************************** */
/*  This function is an error checking version of pipe(2).                    */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when pipe faces error.                                            */
/* ************************************************************************** */
void	ft_x_pipe(int fildes[2], const char *errmsg)
{
	int	ret;

	ret = pipe(fildes);
	if (ret >= 0)
		return ;
	perror(errmsg);
	exit(INTERNAL_ERR_NUM);
}
