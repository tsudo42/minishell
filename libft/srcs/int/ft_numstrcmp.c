/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numstrcmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:11:13 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:14:47 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_int.h"
#include "ft_char.h"
#include "ft_string.h"

/* ************************************************************************** */
/*  This function compared two unsigned integers represented as args.         */
/* ************************************************************************** */
int	ft_numstrcmp(const char *s1, const char *s2)
{
	int	n1;
	int	n2;
	int	i;

	while (*s1 == '0')
		s1++;
	while (*s2 == '0')
		s2++;
	n1 = 0;
	n2 = 0;
	i = 0;
	while (ft_isdigit(s1[i]))
		i++;
	n1 = i;
	i = 0;
	while (ft_isdigit(s2[i]))
		i++;
	n2 = i;
	if (n1 != n2)
		return (n1 - n2);
	return (ft_strncmp(s1, s2, i));
}
