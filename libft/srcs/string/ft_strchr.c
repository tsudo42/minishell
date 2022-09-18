/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 09:05:06 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:54:42 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/* ************************************************************************** */
/*  This function locates the first occurrence of c (converted to a char) in  */
/*  the string pointed to by s. If not found, returns NULL.                   */
/*  The terminating null character is considered to be part of the string;    */
/*  therefore if c is null-char, the functions returns the locale instead of  */
/*  NULL.                                                                     */
/* ************************************************************************** */
char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c && *s != '\0')
		s++;
	if (*s == '\0' && (char)c != '\0')
		return (NULL);
	return ((char *)s);
}
