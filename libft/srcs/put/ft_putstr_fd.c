/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:38:45 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/06 15:16:38 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"
#include <unistd.h>

/* ************************************************************************** */
/*  This function puts string s into file descriptor fd.                      */
/*  If s is NULL, prints "(null)" because the puts() function does so.        */
/* ************************************************************************** */
void	ft_putstr_fd(const char *s, int fd)
{
	size_t	i;

	if (s == NULL)
	{
		write(fd, "(null)", 6);
		return ;
	}
	i = 0;
	while (s[i] != '\0')
	{
		if (i >= 10000000L)
		{
			write(fd, s, 10000000L);
			s += i;
			i = 0;
		}
		i++;
	}
	if (i != 0)
		write(fd, s, i);
}
