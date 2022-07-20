/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_dup.c                                         :+:      :+:    :+:   */
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
/*  This function is an error checking version of dup(2).                     */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when dup faces error.                                             */
/* ************************************************************************** */
int	ft_x_dup(int fildes, const char *errmsg)
{
	int	ret;

	ret = dup(fildes);
	if (ret >= 0)
		return (ret);
	perror(errmsg);
	exit(INTERNAL_ERR_NUM);
}
