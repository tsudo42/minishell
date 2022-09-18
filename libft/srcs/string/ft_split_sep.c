/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/29 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

/* ************************************************************************** */
/*  This helper function allocates (with malloc(3)) and returns an array of   */
/*  strings obtained by splitting s using the second argument as delimiters.  */
/*  This helper function assumes allocated memory `array` which has enough    */
/*  size for containing array of strings.                                     */
/*  The array ends with a NULL pointer.                                       */
/*  This function returns NULL when malloc(3) fails.                          */
/* ************************************************************************** */
static char	**ft_split_sep_helper(char **array, const char *s, const char *sep)
{
	size_t	seplen;
	size_t	n_str;

	n_str = 0;
	while (1)
	{
		seplen = ft_strcspn(s, sep);
		array[n_str] = ft_substr(s, 0, seplen);
		if (array[n_str] == NULL)
		{
			while (n_str-- > 0)
				free(array[n_str]);
			free(array);
			return (NULL);
		}
		n_str++;
		if (s[seplen] == '\0')
			break ;
		else
			s += seplen + 1;
	}
	return (array);
}

/* ************************************************************************** */
/*  This function allocates (with malloc(3)) and returns an array of strings  */
/*  obtained by splitting s using the second argument as delimiters.          */
/*  The array ends with a NULL pointer.                                       */
/*  Like strsep function, the return value may contains blank string (i.e.    */
/*  separating "aa00aa00" with "0" returns {"aa", "", "aa", "", ""}).         */
/*  This function returns NULL when malloc(3) fails.                          */
/* ************************************************************************** */
char	**ft_split_sep(const char *s, const char *sep)
{
	size_t	i;
	size_t	n_sep;
	char	**strs;

	if (s == NULL)
		return (NULL);
	n_sep = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(sep, s[i]) != NULL)
			n_sep++;
		i++;
	}
	strs = malloc(sizeof(char *) * (n_sep + 2));
	if (strs == NULL)
		return (NULL);
	strs[n_sep + 1] = NULL;
	return (ft_split_sep_helper(strs, s, sep));
}
