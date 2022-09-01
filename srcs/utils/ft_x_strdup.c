/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_strdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 08:42:37 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

/* ************************************************************************** */
/*  This function is an error checking version of malloc(3).                  */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when malloc faces error.                                          */
/* ************************************************************************** */
char	*ft_x_strdup(const char *s1, const char *errmsg)
{
	char	*dup;

	dup = ft_strdup(s1);
	if (dup != NULL)
		return (dup);
	perror(errmsg);
	exit(INTERNAL_ERR_NUM);
}
