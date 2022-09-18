/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unbrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:24:23 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:15:01 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_int.h"

/* ************************************************************************** */
/*  This helper function returns the minimum length to represent unsigned     */
/*  integer n in string, including negative sign.                             */
/* ************************************************************************** */
size_t	ft_unbrlen(uintmax_t n, unsigned int base)
{
	size_t	len;

	len = 0;
	while (base <= n)
	{
		n /= base;
		len++;
	}
	len++;
	return (len);
}
