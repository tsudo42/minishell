/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

/* ************************************************************************** */
/*  This function duplicates s with allocating memory with malloc(3),         */
/*  at most len length.                                                       */
/*  s will be null-terminated.                                                */
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
