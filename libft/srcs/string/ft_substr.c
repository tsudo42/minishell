/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:27:49 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 17:59:59 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

/* ************************************************************************** */
/*  This function allocates (with malloc(3)) and returns a substring from     */
/*  the string s.                                                             */
/*  The substring begins at index start and the maximum size of the           */
/*  substring is len.                                                         */
/*  This function returns the starting pointer of the substring, and if       */
/*  malloc(3) fails or s is NULL, returns NULL.                               */
/* ************************************************************************** */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	if (s == NULL)
		return (NULL);
	i = 0;
	while ((i < start || i - start < len) && s[i] != '\0')
		i++;
	if (i > start)
		i -= start;
	else
		i = 0;
	ptr = (char *)malloc(sizeof(char) * (i + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[i] = '\0';
	while (i-- > 0)
		ptr[i] = s[start + i];
	return (ptr);
}
