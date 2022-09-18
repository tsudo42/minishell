/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:40:29 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:52:15 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

/* ************************************************************************** */
/*  This function copies n bytes from memory area src to memory area dst.     */
/*  If dst and src overlap, behavior is undefined.                            */
/*  As the original memcpy function do nothing with dst and src are the       */
/*  same, under that situation this function do nothing either.               */
/* ************************************************************************** */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ptr;

	if (dst == src)
		return (dst);
	ptr = dst;
	while (n-- > 0)
		*ptr++ = *(unsigned char *)src++;
	return (dst);
}
