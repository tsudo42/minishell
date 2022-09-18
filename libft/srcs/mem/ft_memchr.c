/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:53:49 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 17:59:18 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

/* ************************************************************************** */
/*  This function locates the first occurrence of c (converted to an          */
/*  unsigned char) in string s.                                               */
/* ************************************************************************** */
void	*ft_memchr(const void *s, int c, size_t n)
{
	if (s == NULL)
		return (NULL);
	while (n-- > 0)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s++;
	}
	return (NULL);
}
