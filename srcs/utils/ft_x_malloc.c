/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 08:35:54 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* ************************************************************************** */
/*  This function is an error checking version of malloc(3).                  */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when malloc faces error.                                          */
/* ************************************************************************** */
void	*ft_x_malloc(size_t size, const char *errmsg)
{
	void	*ret;

	ret = malloc(size);
	if (ret != NULL)
		return (ret);
	perror(errmsg);
	exit(INTERNAL_ERR_NUM);
}
