/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:32:27 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:13:30 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_int.h"
#include "ft_string.h"

/* ************************************************************************** */
/*  This helper function compares two ulongs,                                 */
/*  one is ulong representation of str, and the other is num.                 */
/*  The abs of return value should not be used, use sign instead (like other  */
/*  cmp functions).                                                           */
/* ************************************************************************** */
static int	my_unsigned_nonzero_slcmp(const char *str, unsigned long num)
{
	size_t			str_len;
	size_t			num_len;
	unsigned long	tmp;

	num_len = 0;
	tmp = num;
	while (tmp > 0 && ++num_len > 0)
		tmp /= 10;
	str_len = 0;
	while ('0' <= str[str_len] && str[str_len] <= '9' && str_len <= num_len)
		str_len++;
	if (num_len != str_len)
		return (str_len - num_len);
	tmp = 1;
	while (num_len-- > 1)
		tmp *= 10;
	while ('0' <= *str && *str <= '9')
	{
		if ((*str - '0') != (int)(num / tmp))
			return ((*str - '0') - (num / tmp));
		num %= tmp;
		tmp /= 10;
		str++;
	}
	return (0);
}

/* ************************************************************************** */
/*  This helper function returns LONG_MAX or LONG_MIN if num_str represents   */
/*  over LONG_MAX with sign>0, or num_str represents over abs(LONG_MIN-1)     */
/*  with sign<0, respectively.                                                */
/*  Otherwise, this function returns 0.                                       */
/* ************************************************************************** */
static long	my_ato_llimits(const char *num_str, const int sign)
{
	if (sign > 0 && my_unsigned_nonzero_slcmp(num_str, LONG_MAX) >= 0)
		return (LONG_MAX);
	if (sign < 0 && my_unsigned_nonzero_slcmp(num_str, -(LONG_MIN + 1)) > 0)
		return (LONG_MIN);
	return (0);
}

/* ************************************************************************** */
/*  This function converts the initial portion of the string pointed to by    */
/*  str to int representation.                                                */
/*  This function equivalent to: (int)strtol(str, (char **)NULL, 10); unless  */
/*  strtol uses errno.                                                        */
/* ************************************************************************** */
int	ft_atoi(const char *str)
{
	char	sign;
	long	val;

	while (*str != '\0' && ft_strchr("\t\n\v\f\r ", *str) != NULL)
		str++;
	sign = 1;
	if ((*str == '+' || *str == '-') && *(str++) == '-')
		sign = -1;
	while (*str == '0')
		str++;
	val = my_ato_llimits(str, sign);
	if (val != 0)
		return ((int)val);
	while ('0' <= *str && *str <= '9')
	{
		val *= 10;
		val += *str - '0';
		str++;
	}
	return ((int)(val * sign));
}
