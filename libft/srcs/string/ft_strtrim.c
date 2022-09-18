/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:37:17 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:00:05 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

/* ************************************************************************** */
/*  This function allocates (with malloc(3)) and returns a copy of s1 with    */
/*  the characters specified in set removed from the beginning and the end    */
/*  of the string.                                                            */
/*  This function returns the pointer to the trimmed string, and if malloc    */
/*  fails or s1 is NULL, returns NULL;                                        */
/* ************************************************************************** */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*ptr;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	while (*s1 != '\0' && ft_strchr(set, *s1) != NULL)
		s1++;
	if (*s1 == '\0')
		return (ft_strdup(""));
	i = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]) != NULL && i > 0)
		i--;
	ptr = (char *)malloc(sizeof(char) * (i + 2));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, i + 2);
	return (ptr);
}
