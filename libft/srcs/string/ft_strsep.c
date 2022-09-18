/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/29 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/* ************************************************************************** */
/*  This function locates, in the string referenced by *stringp, the first    */
/*  occurrence of any character in the string delim (or the terminating ‘\0’  */
/*  character) and replaces it with a ‘\0’.                                   */
/*  If *stringp is initially NULL, strsep() returns NULL.                     */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strsep(char **stringp, const char *delim)
{
	char	*ret;

	if (stringp == NULL || *stringp == NULL)
		return (NULL);
	ret = *stringp;
	*stringp += ft_strcspn(*stringp, delim);
	if (**stringp != '\0')
	{
		**stringp = '\0';
		(*stringp)++;
	}
	else
		*stringp = NULL;
	return (ret);
}
