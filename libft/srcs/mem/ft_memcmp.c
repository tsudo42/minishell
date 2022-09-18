/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:54:28 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:52:02 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

/* ************************************************************************** */
/*  This function compares byte string s1 against byte string s2.             */
/*  Both strings are assumed to be n bytes long.                              */
/* ************************************************************************** */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n-- > 0)
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
			return (*(unsigned char *)s1 - (int)*(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}
