/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

/* ************************************************************************** */
/*  This function is an error checking version of signal(3).                  */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when pipe faces error.                                            */
/* ************************************************************************** */
void	(*ft_x_signal(int sig, void (*func)(int), const char *errmsg))(int s)
{
	void	(*ret)(int);

	ret = signal(sig, func);
	if (ret != SIG_ERR)
		return (ret);
	perror(errmsg);
	exit(INTERNAL_ERR_NUM);
}
