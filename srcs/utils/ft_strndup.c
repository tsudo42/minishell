/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:23:08 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:55:19 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* ************************************************************************** */
/*  This function duplicates s with allocating memory with malloc(3),         */
/*  at most len length.                                                       */
/* ************************************************************************** */
char	*ft_strndup(const char *s, size_t len)
{
	char	*ptr;

	len = ft_strnlen(s, len);
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr != NULL)
		ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}
