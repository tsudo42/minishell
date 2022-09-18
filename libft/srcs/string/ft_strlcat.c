/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:06:03 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:56:24 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/* ************************************************************************** */
/*  This function concatenates strings from src to dst, and returns the       */
/*  number of chars of dst+src if dstsize were infinite.                      */
/* ************************************************************************** */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = ft_strnlen(dst, dstsize);
	return (i + ft_strlcpy(dst + i, src, dstsize - i));
}
