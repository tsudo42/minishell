/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isintstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:33:29 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 18:53:39 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_int.h"
#include "ft_char.h"
#include "ft_string.h"

/* ************************************************************************** */
/*  This function checks if arg#1 is representation of int.                   */
/*  Integers over INT_MAX or lower than INT_MIN wont be considered as int.    */
/* ************************************************************************** */
int	ft_isintstr(const char *str)
{
	int		sign;
	size_t	i;
	char	digits[11];

	sign = 0;
	if (str[0] == '+')
		str++;
	else if (str[0] == '-')
		sign = 1;
	if (ft_strlcpy(digits, str + sign, 11) >= 11)
		return (0);
	if (digits[0] == '\0')
		return (0);
	i = 0;
	while (digits[i] != '\0')
	{
		if (!ft_isdigit(digits[i]))
			return (0);
		i++;
	}
	if (i == 10 && \
		((sign == 0 && ft_strncmp(digits, "2147483647", 11) > 0) || \
		(sign == 1 && ft_strncmp(digits, "2147483648", 11) > 0)))
		return (0);
	return (1);
}
