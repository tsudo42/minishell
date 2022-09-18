/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:22:51 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:59:42 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/* ************************************************************************** */
/*  This function searches for the string needle inside the string haystack,  */
/*  at most len characters. If found, returns the pointer of the beginning    */
/*  of the first occurence, and if not, returns NULL.                         */
/* ************************************************************************** */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (*needle == '\0')
		return ((char *)haystack);
	while (len-- > 0)
	{
		i = 0;
		while (haystack[i] == needle[i])
		{
			if (needle[i + 1] == '\0')
				return ((char *)haystack);
			if (i >= len)
				return (NULL);
			i++;
		}
		if (haystack[i] == '\0')
			return (NULL);
		haystack++;
	}
	return (NULL);
}
