/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:53:18 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:01:55 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"
#include <unistd.h>

/* ************************************************************************** */
/*  This function puts number represented by n into file descriptor fd.       */
/*  Bufsize of str_n must be at least 1.                                      */
/* ************************************************************************** */
void	ft_putnbr_fd(int n, int fd)
{
	char		str_n[42];
	signed int	i_str;

	if (n < 0)
		write(fd, "-", 1);
	i_str = 42;
	while (--i_str >= 0)
	{
		str_n[i_str] = (n % 10) * (1 - 2 * (n < 0)) + '0';
		n /= 10;
		if (n == 0)
		{
			write(fd, &str_n[i_str], 42 - i_str);
			return ;
		}
	}
	if (n < 0)
		n = -n;
	ft_putnbr_fd(n, fd);
	write(fd, str_n, 42);
}
