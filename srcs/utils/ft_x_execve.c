/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_execve.c                                      :+:      :+:    :+:   */
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
/*  This function is an error checking version of execve(2).                  */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when execve faces error.                                          */
/* ************************************************************************** */
void	ft_x_execve(const char *path, char *const argv[], char *const envp[], \
	const char *errmsg)
{
	execve(path, argv, envp);
	perror(errmsg);
	exit(INTERNAL_ERR_NUM);
}
