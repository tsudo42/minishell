/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 17:48:38 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/06 18:30:39 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/* ************************************************************************** */
/*  it computes the string array index of the first character of s which is   */
/*  not in charset, else the index of the first null character.               */
/*  Unlike the original strspn, this consideres NULL arg as blank string.     */
/* ************************************************************************** */
size_t	ft_strspn(const char *s, const char *charset)
{
	size_t	i;

	if (s == NULL || charset == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(charset, s[i]) == NULL)
			break ;
		i++;
	}
	return (i);
}
