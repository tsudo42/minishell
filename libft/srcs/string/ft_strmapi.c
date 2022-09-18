/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 18:34:58 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:57:11 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <limits.h>
#include <stdlib.h>

/* ************************************************************************** */
/*  Applies the function f to each character of the string s to create a new  */
/*  string (with malloc(3)) resulting from successive applications of f.      */
/* ************************************************************************** */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*ptr;

	if (s == NULL)
		return (NULL);
	if (f == NULL)
		return (ft_strdup(s));
	i = ft_strlen(s);
	if (i > UINT_MAX)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (i + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
