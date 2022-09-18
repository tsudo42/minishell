/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 17:45:54 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/06 20:30:10 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/* ************************************************************************** */
/*  This function isolates sequential tokens in a string separated by sep.    */
/*  Unlike the original strspn, this consideres NULL arg as blank string.     */
/* ************************************************************************** */
char	*ft_strtok(char *str, const char *sep)
{
	static char	*remnant;
	char		*tmp;
	size_t		i;

	if (str == NULL && remnant == NULL)
		return (NULL);
	if (remnant == NULL || str != NULL)
		remnant = str;
	remnant += ft_strspn(remnant, sep);
	i = ft_strcspn(remnant, sep);
	if (remnant[0] == '\0')
	{
		remnant = NULL;
		return (NULL);
	}
	tmp = remnant;
	if (remnant[i] == '\0')
		remnant = NULL;
	else
	{
		remnant[i] = '\0';
		remnant += i + 1;
	}
	return (tmp);
}
