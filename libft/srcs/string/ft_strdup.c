/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:23:08 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:55:19 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

/* ************************************************************************** */
/*  This function duplicates s1 with allocating memory with malloc(3).        */
/* ************************************************************************** */
char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*ptr;

	i = 0;
	while (s1[i] != '\0')
		i++;
	ptr = malloc(++i * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i-- > 0)
		ptr[i] = s1[i];
	return (ptr);
}
