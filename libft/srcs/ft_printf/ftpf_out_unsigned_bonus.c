/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_out_unsigned_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 22:02:53 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/08 17:35:35 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"
#include "ft_int.h"

static void	ftpf_out_unsigned_2(t_ftpf *param, int base, int cap);

static uintmax_t	ftpf_unsigned_getarg(t_ftpf *param)
{
	uintmax_t	u;

	if (param->conv->length == FTPF_CHAR)
	{
		u = va_arg(param->args, unsigned int);
		u = (unsigned char)u;
	}
	else if (param->conv->length == FTPF_SHORT)
	{
		u = va_arg(param->args, unsigned int);
		u = (unsigned short)u;
	}
	else if (param->conv->length == FTPF_LLONG)
		u = va_arg(param->args, unsigned long long);
	else if (param->conv->length == FTPF_LONG)
		u = va_arg(param->args, unsigned long);
	else if (param->conv->length == FTPF_SIZE_T)
		u = va_arg(param->args, size_t);
	else if (param->conv->length == FTPF_INTMAX_T)
		u = va_arg(param->args, uintmax_t);
	else if (param->conv->length == FTPF_PTRDIFF_T)
		u = va_arg(param->args, unsigned long);
	else
		u = va_arg(param->args, unsigned int);
	return (u);
}

static void	ftpf_unsigned_countlen_helper(uintmax_t u, int base, t_ftpf *param)
{
	t_ftpf_conv	*conv;

	conv = param->conv;
	if (u == 0 && conv->precision == 0 && \
		(*(param->fmt) != 'o' || !(conv->flags & FTPF_HASH)))
		conv->datalen = 0;
	conv->zeropadlen = conv->precision - conv->datalen;
	if (conv->flags & FTPF_HASH && base == 8)
		conv->zeropadlen--;
	if (conv->zeropadlen < 0)
		conv->zeropadlen = 0;
}

static void	ftpf_unsigned_countlen(uintmax_t u, int base, t_ftpf *param)
{
	t_ftpf_conv	*conv;
	int			spacepadlen_tmp;

	conv = param->conv;
	if (conv->flags & FTPF_HASH && base == 8)
		conv->prefixlen = 1;
	if (conv->flags & FTPF_HASH && base == 16)
		conv->prefixlen = 2;
	conv->datalen = ft_unbrlen(u, base);
	if (conv->flags & FTPF_DOT)
	{
		ftpf_unsigned_countlen_helper(u, base, param);
	}
	spacepadlen_tmp = conv->minfield - \
		(conv->prefixlen + conv->zeropadlen + conv->datalen);
	if (conv->flags & (FTPF_DOT | FTPF_MINUS) || !(conv->flags & FTPF_ZERO))
		conv->spacepadlen = spacepadlen_tmp;
	else
		conv->zeropadlen = spacepadlen_tmp;
}

void	ftpf_out_unsigned(t_ftpf *param)
{
	if (param->conv->minfield >= 2147483646 || \
		param->conv->precision >= 2147483646)
		param->errnum = EOVERFLOW;
	if (*(param->fmt) == 'u')
		ftpf_out_unsigned_2(param, 10, 0);
	else if (*(param->fmt) == 'o')
		ftpf_out_unsigned_2(param, 8, 0);
	else if (*(param->fmt) == 'x')
		ftpf_out_unsigned_2(param, 16, 0);
	else if (*(param->fmt) == 'X')
		ftpf_out_unsigned_2(param, 16, 1);
	else if (*(param->fmt) == 'p')
	{
		param->conv->length = FTPF_LONG;
		param->conv->flags |= FTPF_HASH;
		ftpf_out_unsigned_2(param, 16, 0);
	}
}

static void	ftpf_out_unsigned_2(t_ftpf *param, int base, int cap)
{
	uintmax_t	u;

	u = ftpf_unsigned_getarg(param);
	if (u == 0 && *(param->fmt) != 'p')
		base = 10;
	ftpf_unsigned_countlen(u, base, param);
	if (!(param->conv->flags & FTPF_MINUS))
		ftpf_putpad(' ', param->conv->spacepadlen, param);
	if (param->conv->flags & FTPF_HASH && base == 8)
		ftpf_write("0", 1, param);
	if (param->conv->flags & FTPF_HASH && base == 16)
	{
		if (cap)
			ftpf_write("0X", 2, param);
		else
			ftpf_write("0x", 2, param);
	}
	ftpf_putpad('0', param->conv->zeropadlen, param);
	if (param->conv->datalen != 0)
		ftpf_putunbr(u, base, cap, param);
	if (param->conv->flags & FTPF_MINUS)
		ftpf_putpad(' ', param->conv->spacepadlen, param);
	param->fmt++;
}
