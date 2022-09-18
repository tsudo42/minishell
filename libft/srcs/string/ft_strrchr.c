/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:28:14 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:59:54 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/* ************************************************************************** */
/*  This function locates the last occurrence of c (converted to a char) in   */
/*  the string pointed to by s. If not found, returns NULL.                   */
/*  The terminating null character is considered to be part of the string;    */
/*  therefore if c is null-char, the functions returns the locale instead of  */
/*  NULL.                                                                     */
/* ************************************************************************** */
char	*ft_strrchr(const char *s, int c)
{
	char	*ret;

	ret = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			ret = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		ret = (char *)s;
	return (ret);
}
