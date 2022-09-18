/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:12:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/25 19:13:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

/* ************************************************************************** */
/*  This function allocates (with malloc(3)) and returns a new string, which  */
/*  is the result of the concatenation of s1, s2, and s3.                     */
/* ************************************************************************** */
char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	size_t	total_len;
	char	*ptr;

	if (s1 == NULL)
		return (ft_strjoin(s2, s3));
	if (s2 == NULL)
		return (ft_strjoin(s1, s3));
	if (s3 == NULL)
		return (ft_strjoin(s1, s2));
	total_len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	ptr = (char *)malloc(sizeof(char) * total_len);
	if (ptr == NULL)
		return (NULL);
	*ptr = '\0';
	ft_strlcat(ptr, s1, total_len);
	ft_strlcat(ptr, s2, total_len);
	ft_strlcat(ptr, s3, total_len);
	return (ptr);
}
