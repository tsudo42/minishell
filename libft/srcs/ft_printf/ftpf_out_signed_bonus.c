/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_out_signed_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 22:01:31 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 17:47:59 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"
#include "ft_int.h"

static intmax_t	ftpf_signed_getarg(t_ftpf *param)
{
	intmax_t	d;

	if (param->conv->length == FTPF_CHAR)
	{
		d = va_arg(param->args, int);
		d = (char)d;
	}
	else if (param->conv->length == FTPF_SHORT)
	{
		d = va_arg(param->args, int);
		d = (short)d;
	}
	else if (param->conv->length == FTPF_LLONG)
		d = va_arg(param->args, long long);
	else if (param->conv->length == FTPF_LONG)
		d = va_arg(param->args, long);
	else if (param->conv->length == FTPF_SIZE_T)
		d = (va_arg(param->args, long));
	else if (param->conv->length == FTPF_INTMAX_T)
		d = va_arg(param->args, intmax_t);
	else if (param->conv->length == FTPF_PTRDIFF_T)
		d = va_arg(param->args, ptrdiff_t);
	else
		d = va_arg(param->args, int);
	return (d);
}

static void	ftpf_signed_countlen(intmax_t d, int base, t_ftpf *param)
{
	t_ftpf_conv	*conv;
	int			spacepadlen_tmp;

	conv = param->conv;
	conv->prefixlen = 0;
	if (d < 0 || (conv->flags & (FTPF_PLUS | FTPF_SPACE)))
		conv->prefixlen++;
	(void)base;
	conv->datalen = ft_nbrlen(d, 10);
	if (d < 0)
		conv->datalen--;
	if (conv->flags & FTPF_DOT)
	{
		if (d == 0 && conv->precision == 0)
			conv->datalen = 0;
		conv->zeropadlen = conv->precision - conv->datalen;
		if (conv->zeropadlen < 0)
			conv->zeropadlen = 0;
	}
	spacepadlen_tmp = conv->minfield - \
		(conv->prefixlen + conv->zeropadlen + conv->datalen);
	if (conv->flags & (FTPF_MINUS | FTPF_DOT) || !(conv->flags & FTPF_ZERO))
		conv->spacepadlen = spacepadlen_tmp;
	else
		conv->zeropadlen = spacepadlen_tmp;
}

void	ftpf_out_signed(t_ftpf *param)
{
	intmax_t	d;

	if (param->conv->minfield >= 2147483646 || \
		param->conv->precision >= 2147483646)
		param->errnum = EOVERFLOW;
	d = ftpf_signed_getarg(param);
	ftpf_signed_countlen(d, 10, param);
	if (!(param->conv->flags & FTPF_MINUS))
		ftpf_putpad(' ', param->conv->spacepadlen, param);
	if (d < 0)
		ftpf_write("-", 1, param);
	else if (param->conv->flags & FTPF_PLUS)
		ftpf_write("+", 1, param);
	else if (param->conv->flags & FTPF_SPACE)
		ftpf_write(" ", 1, param);
	ftpf_putpad('0', param->conv->zeropadlen, param);
	if (param->conv->datalen != 0)
		ftpf_putnbr(d, 10, 0, param);
	if (param->conv->flags & FTPF_MINUS)
		ftpf_putpad(' ', param->conv->spacepadlen, param);
	param->fmt++;
}
