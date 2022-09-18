/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 23:32:26 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:52:27 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

/* ************************************************************************** */
/*  This function copies len bytes from string src to string dst.             */
/*  The two strings may overlap;                                              */
/*  the copy is always done in a non-destructive manner.                      */
/* ************************************************************************** */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptr;

	if (dst < src)
		return (ft_memcpy(dst, src, len));
	if (dst == NULL && src == NULL)
		return (NULL);
	ptr = dst + len - 1;
	src += len - 1;
	while (len-- > 0)
		*ptr-- = *(unsigned char *)src--;
	return (dst);
}
