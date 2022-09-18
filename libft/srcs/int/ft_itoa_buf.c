/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_buf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:43:25 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:13:49 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_int.h"

/* ************************************************************************** */
/*  This helper function swaps memory range [left, right].                    */
/* ************************************************************************** */
static void	*ft_memswap(void *left, void *right)
{
	void			*ret;
	unsigned char	tmp;

	ret = left;
	while (left < right)
	{
		tmp = *(unsigned char *)right;
		*(unsigned char *)right = *(unsigned char *)left;
		*(unsigned char *)left = tmp;
		right--;
		left++;
	}
	return (ret);
}

/* ************************************************************************** */
/*  This function takes buffer as argument and returns a string representing  */
/*  the integer received as an argument.                                      */
/*  If buffer is too small, this function returns NULL.                       */
/*  Almost same algorithm as ft_itoa.                                         */
/* ************************************************************************** */
char	*ft_itoa_buf(int n, char *buf, size_t buflen)
{
	char	*left;
	char	*right;

	if (buf == NULL || buflen < ft_intlen(n) + 1)
		return (NULL);
	left = buf;
	right = buf;
	if (n <= 0)
	{
		*left++ = "0-"[n < 0];
		right++;
	}
	while (n != 0)
	{
		*right++ = (n % 10) * (1 - 2 * (n < 0)) + '0';
		n /= 10;
	}
	*right-- = '\0';
	ft_memswap(left, right);
	return (buf);
}
