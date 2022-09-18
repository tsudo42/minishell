/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:39:16 by tsudo             #+#    #+#             */
/*   Updated: 2022/02/14 09:07:49 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_string.h"
#include <limits.h>
#include <stdarg.h>
#include <unistd.h>

static int	ft_ret_handler(ssize_t val, int reset)
{
	static ssize_t	ret;
	int				tmp;

	if (ret >= 0)
	{
		if (val < 0)
			ret = val;
		else
			ret += val;
		if (ret >= INT_MAX)
			ret = -1;
	}
	if (reset)
	{
		tmp = ret;
		ret = 0;
		return (tmp);
	}
	return (ret);
}

static int	ft_puts(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (ft_ret_handler(write(1, "(null)", 6), 0));
	i = 0;
	while (s[i] != '\0')
		i++;
	return (ft_ret_handler(write(1, s, i), 0));
}

static int	ft_put_unum_base(unsigned long num, int base, int cap)
{
	char	*d_arr;
	char	num_str[sizeof(unsigned long) * 3];
	int		ofs;

	d_arr = "0123456789abcdef";
	if (cap)
		d_arr = "0123456789ABCDEF";
	ofs = sizeof(unsigned long) * 3;
	while (num >= (unsigned int)base)
	{
		num_str[--ofs] = d_arr[num % base];
		num /= base;
	}
	num_str[--ofs] = d_arr[num];
	ft_ret_handler(write(1, &num_str[ofs], sizeof(unsigned long) * 3 - ofs), 0);
	return (ft_ret_handler(0, 0));
}

int	ft_parse(char c, long n)
{
	if (c == 'd' || c == 'i')
	{
		if (n >= 0)
			return (ft_put_unum_base((int)n, 10, 0));
		else if (ft_ret_handler(write(1, "-", 1), 0) > 0)
			ft_put_unum_base(-n, 10, 0);
		return (ft_ret_handler(0, 0));
	}
	else if (c == 'u')
		return (ft_put_unum_base((unsigned int)n, 10, 0));
	else if (c == 'x')
		return (ft_put_unum_base((unsigned int)n, 16, 0));
	else if (c == 'X')
		return (ft_put_unum_base((unsigned int)n, 16, 1));
	else if (c == 's')
		return (ft_puts((const char *)n));
	else if (c == 'p' && ft_ret_handler(write(1, "0x", 2), 0) > 0)
	{
		ft_put_unum_base(n, 16, 0);
		return (ft_ret_handler(0, 0));
	}
	n = (unsigned char)n;
	if (c == 'c')
		return (ft_ret_handler(write(1, &n, 1), 0));
	return (ft_ret_handler(-1, 0));
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;

	ft_ret_handler(0, 1);
	va_start(args, fmt);
	while (ft_ret_handler(0, 0) >= 0 && *fmt != '\0')
	{
		if (*fmt == '%')
		{
			fmt++;
			if (*fmt == '\0')
				break ;
			if (ft_strchr("cdiuxX", *fmt) != NULL)
				ft_parse(*fmt, va_arg(args, int));
			else if (ft_strchr("sp", *fmt) != NULL)
				ft_parse(*fmt, (long)va_arg(args, void *));
			else
				ft_ret_handler(write(1, fmt, 1), 0);
		}
		else
			ft_ret_handler(write(1, fmt, 1), 0);
		fmt++;
	}
	va_end(args);
	return (ft_ret_handler(0, 1));
}
