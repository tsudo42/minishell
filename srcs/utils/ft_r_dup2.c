/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_r_dup2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/24 11:48:55 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* ************************************************************************** */
/*  This function is an error checking version of dup2(2).                    */
/*  This function prints an error message and return -1 when dup2 faces       */
/*  error.                                                                    */
/* ************************************************************************** */
int	ft_r_dup2(int fildes, int fildes2, const char *errmsg)
{
	int	ret;

	ret = dup2(fildes, fildes2);
	if (ret >= 0)
		return (ret);
	perror(errmsg);
	return (-1);
}
