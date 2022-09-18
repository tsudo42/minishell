/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:34:34 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:55:43 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

/* ************************************************************************** */
/*  This function allocates (with malloc(3)) and returns a new string, which  */
/*  is the result of the concatenation of s1 and s2.                          */
/* ************************************************************************** */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ptr;

	if (s1 == NULL)
	{
		if (s2 == NULL)
			return (ft_strdup(""));
		return (ft_strdup(s2));
	}
	if (s2 == NULL)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, s1_len + 1);
	ft_strlcpy(ptr + s1_len, s2, s2_len + 1);
	return (ptr);
}
