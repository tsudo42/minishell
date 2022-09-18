/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:42:25 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:54:36 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

/* ************************************************************************** */
/*  This helper function allocates (with malloc(3)) and returns an array of   */
/*  strings obtained by splitting s using the character c as a delimiter.     */
/*  This helper function assumes allocated memory `array` which has enough    */
/*  size for containing array of strings.                                     */
/*  The array ends with a NULL pointer.                                       */
/*  This function returns NULL when malloc(3) fails.                          */
/* ************************************************************************** */
static char	**ft_split_helper(char **array, char const *s, char c)
{
	size_t	n_str;
	size_t	n_chr;

	n_str = 0;
	while (*s != '\0')
	{
		n_chr = 0;
		while (s[n_chr] != c && s[n_chr] != '\0')
			n_chr++;
		array[n_str] = (char *)malloc(sizeof(char) * (n_chr + 1));
		if (array[n_str] == NULL)
		{
			while (n_str-- > 0)
				free(array[n_str]);
			free(array);
			return (NULL);
		}
		ft_strlcpy(array[n_str++], s, n_chr + 1);
		s += n_chr;
		while (*s == c && *s != '\0')
			s++;
	}
	array[n_str] = NULL;
	return (array);
}

/* ************************************************************************** */
/*  This function allocates (with malloc(3)) and returns an array of strings  */
/*  obtained by splitting s using the character c as a delimiter.             */
/*  The array ends with a NULL pointer.                                       */
/*  This function returns NULL when malloc(3) fails.                          */
/* ************************************************************************** */
char	**ft_split(char const *s, char c)
{
	size_t	n_str;
	char	*tmp;
	char	**array;

	while (s != NULL && *s == c && *s != '\0')
		s++;
	n_str = 0;
	if (s != NULL)
	{
		tmp = (char *)s;
		while (*tmp != '\0')
		{
			while (*tmp != c && *tmp != '\0')
				tmp++;
			n_str++;
			while (*tmp == c && *tmp != '\0')
				tmp++;
		}
	}
	array = (char **)malloc(sizeof(char *) * (n_str + 1));
	if (array != NULL)
		array[n_str] = NULL;
	if (array == NULL || s == NULL)
		return (array);
	return (ft_split_helper(array, s, c));
}
