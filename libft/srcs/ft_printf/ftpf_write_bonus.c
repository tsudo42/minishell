/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_write_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 18:18:01 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 17:48:10 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"
#include "ft_mem.h"
#include <unistd.h>

int	ftpf_write(const void *buf, size_t nbyte, t_ftpf *param)
{
	int	ret;

	if (param->errnum != 0)
		param->ret = -1;
	if (param->ret >= 0)
	{
		if ((size_t)param->ret + nbyte >= INT_MAX)
		{
			ret = -1;
			param->errnum = EOVERFLOW;
			return (-1);
		}
		ret = write(param->fd, buf, nbyte);
		if (ret < 0)
			param->ret = ret;
		else
			param->ret += ret;
		return (ret);
	}
	return (param->ret);
}

int	ftpf_putpad(int pad, int nbyte, t_ftpf *param)
{
	int		ret;
	char	buf[42];

	if (param->errnum != 0)
		param->ret = -1;
	if (nbyte <= 0 || param->ret < 0)
		return (0);
	if (nbyte + (size_t)param->ret >= INT_MAX)
	{
		param->ret = -1;
		param->errnum = EOVERFLOW;
		return (-1);
	}
	ft_memset(buf, pad, 42);
	ret = 0;
	while (nbyte >= 42 && ret >= 0)
	{
		ret = ftpf_write(buf, 42, param);
		nbyte -= 42;
	}
	if (nbyte > 0 && ret >= 0)
		ftpf_write(buf, nbyte, param);
	return (param->ret);
}

void	ftpf_putnbr(intmax_t n, int base, int cap, t_ftpf *param)
{
	if (n >= 0)
	{
		ftpf_putunbr(n, base, cap, param);
	}
	else
	{
		if (n <= -10)
			ftpf_putunbr(-(n / 10), base, cap, param);
		ftpf_putunbr(-(n % 10), base, cap, param);
	}
}

void	ftpf_putunbr(uintmax_t n, int base, int cap, t_ftpf *param)
{
	char		*num_str;
	char		str_n[42];
	signed int	i_str;

	i_str = 42;
	if (cap)
		num_str = "0123456789ABCDEF";
	else
		num_str = "0123456789abcdef";
	while (--i_str >= 0)
	{
		str_n[i_str] = num_str[n % base];
		n /= base;
		if (n == 0)
		{
			ftpf_write(&str_n[i_str], 42 - i_str, param);
			return ;
		}
	}
	ftpf_putunbr(n, base, cap, param);
	ftpf_write(str_n, 42, param);
}
