/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:20:27 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:14:39 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_int.h"

/* ************************************************************************** */
/*  This helper function returns the minimum length to represent integer n    */
/*  in string, including negative sign.                                       */
/* ************************************************************************** */
size_t	ft_nbrlen(intmax_t n, int base)
{
	size_t	len;

	len = 0;
	if (n < 0)
		len++;
	while (n <= -base || base <= n)
	{
		n /= base;
		len++;
	}
	len++;
	return (len);
}
