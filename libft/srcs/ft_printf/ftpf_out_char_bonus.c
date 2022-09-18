/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_out_char_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 22:18:59 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/08 17:01:30 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"
#include <wchar.h>

static void	ftpf_wc(t_ftpf *param)
{
	wchar_t	wc;

	wc = va_arg(param->args, wint_t);
	if (wc > 0xFF || wc < 0)
	{
		param->errnum = EILSEQ;
	}
	if (!(param->conv->flags & FTPF_MINUS))
		ftpf_putpad(' ', param->conv->spacepadlen, param);
	ftpf_putpad('0', param->conv->zeropadlen, param);
	if (param->conv->datalen != 0)
		ftpf_write(&wc, 1, param);
	if (param->conv->flags & FTPF_MINUS)
		ftpf_putpad(' ', param->conv->spacepadlen, param);
	param->fmt++;
}

static void	ftpf_char_countlen(t_ftpf *param)
{
	t_ftpf_conv	*conv;

	conv = param->conv;
	conv->datalen = 1;
	if (conv->flags & FTPF_MINUS || !(conv->flags & FTPF_ZERO))
		conv->spacepadlen = conv->minfield - 1;
	else
		conv->zeropadlen = conv->minfield - 1;
}

void	ftpf_out_char(t_ftpf *param)
{
	unsigned char	c;

	if (param->conv->minfield >= 2147483646)
		param->errnum = EOVERFLOW;
	ftpf_char_countlen(param);
	if (*(param->fmt) == 'C')
		param->conv->length = FTPF_LONG;
	if (*(param->fmt) != '%' && \
		(param->conv->length == FTPF_LONG || param->conv->length == FTPF_LLONG))
	{
		ftpf_wc(param);
		return ;
	}
	if (*(param->fmt) != '%')
		c = va_arg(param->args, int);
	else
		c = '%';
	if (!(param->conv->flags & FTPF_MINUS))
		ftpf_putpad(' ', param->conv->spacepadlen, param);
	ftpf_putpad('0', param->conv->zeropadlen, param);
	if (param->conv->datalen != 0)
		ftpf_write(&c, 1, param);
	if (param->conv->flags & FTPF_MINUS)
		ftpf_putpad(' ', param->conv->spacepadlen, param);
	param->fmt++;
}
