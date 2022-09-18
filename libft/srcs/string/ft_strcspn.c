/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 18:02:24 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/06 18:30:31 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/* ************************************************************************** */
/*  This funcion computes the string array index of the first character of s  */
/*  which is also in charset, else the index of the first null character.     */
/*  Unlike the original strcspn, this consideres NULL arg as blank string.    */
/* ************************************************************************** */
size_t	ft_strcspn(const char *s, const char *charset)
{
	size_t	i;

	if (s == NULL)
		return (0);
	if (charset == NULL)
		return (ft_strlen(s));
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(charset, s[i]) != NULL)
			break ;
		i++;
	}
	return (i);
}
