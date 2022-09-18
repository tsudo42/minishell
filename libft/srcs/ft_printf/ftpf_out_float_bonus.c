/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_out_float_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 22:23:20 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 17:47:55 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"
#include "ft_string.h"

static void	ftpf_out_float1(t_ftpf_float *fl, char type, t_ftpf *param);
static void	ftpf_out_floatg(t_ftpf_float *fl, char type, t_ftpf *param);
static void	ftpf_out_float2(t_ftpf_float *fl, char type, t_ftpf *param);
static void	ftpf_out_float3(t_ftpf_float *fl, char type, t_ftpf *param);

void	ftpf_out_float(t_ftpf *param)
{
	t_ftpf_float	fl;
	double			d;
	long double		ld;
	int				ret;

	if (!(param->conv->flags & FTPF_DOT))
		param->conv->precision = 6;
	if (param->conv->length != FTPF_LDOUBLE)
	{
		d = va_arg(param->args, double);
		ret = ftpf_dbl_getdata(&fl, d);
	}
	else
	{
		ld = va_arg(param->args, long double);
		d = ld;
		ret = ftpf_dbl_getdata(&fl, d);
	}
	if (ret == 0)
		ftpf_out_float1(&fl, '_', param);
	else
	{
		ftpf_dbl_other(&fl, param);
		ftpf_out_float2(&fl, 'n', param);
	}
}

static void	ftpf_out_float1(t_ftpf_float *fl, char type, t_ftpf *param)
{
	type = 'f';
	if (ft_strchr("eE", *(param->fmt)) != NULL)
		type = 'e';
	if (ft_strchr("gG", *(param->fmt)) != NULL)
	{
		if (param->conv->precision <= 0)
			param->conv->precision = 1;
		if (fl->e0 < -4 || param->conv->precision <= fl->e0)
			type = 'e';
		if (type == 'f')
			param->conv->precision -= fl->e0 + 1;
		else
			param->conv->precision -= 1;
	}
	if (type == 'f')
		ftpf_trimdata(fl, fl->e0, param);
	else
		ftpf_trimdata(fl, 0, param);
	if (ft_strchr("gG", *(param->fmt)) != NULL)
		ftpf_out_floatg(fl, type, param);
	ftpf_out_float2(fl, type, param);
}

static void	ftpf_out_floatg(t_ftpf_float *fl, char type, t_ftpf *param)
{
	int	i;

	if (param->conv->flags & FTPF_HASH)
		return ;
	if (type == 'f')
		i = fl->e0 + param->conv->precision;
	else
		i = param->conv->precision;
	if (i < 0)
	{
		param->conv->precision = 0;
		return ;
	}
	if (i >= (int)ft_strlen(fl->buf))
		i = ft_strlen(fl->buf) - 1;
	while (i > 0 && fl->buf[i] == '0')
		i--;
	if (type == 'f')
		param->conv->precision = i - fl->e0;
	else
		param->conv->precision = i;
	if (param->conv->precision < 0)
		param->conv->precision = 0;
}

static void	ftpf_out_float2(t_ftpf_float *fl, char type, t_ftpf *param)
{
	param->conv->datalen = 1;
	if (param->conv->precision > 0 || param->conv->flags & FTPF_HASH)
		param->conv->datalen++;
	if (type == 'f')
	{
		param->conv->datalen += param->conv->precision;
		if (fl->e0 >= 0)
			param->conv->datalen += fl->e0;
	}
	else if (type == 'e')
	{
		param->conv->datalen += param->conv->precision + 4;
		if (fl->e0 < -99 || 99 < fl->e0)
			param->conv->datalen++;
	}
	else
	{
		param->conv->flags &= (FTPF_MINUS | FTPF_PLUS | FTPF_SPACE);
		param->conv->datalen = ft_strlen(fl->buf);
	}
	ftpf_out_float3(fl, type, param);
	param->fmt++;
}

static void	ftpf_out_float3(t_ftpf_float *fl, char type, t_ftpf *param)
{
	if (fl->sign || (param->conv->flags & (FTPF_SPACE | FTPF_PLUS)))
		param->conv->datalen++;
	if (param->conv->minfield < param->conv->datalen)
		param->conv->minfield = param->conv->datalen;
	if (param->conv->flags & FTPF_MINUS || !(param->conv->flags & FTPF_ZERO))
		param->conv->spacepadlen = param->conv->minfield - param->conv->datalen;
	else
		param->conv->zeropadlen = param->conv->minfield - param->conv->datalen;
	if (!(param->conv->flags & FTPF_MINUS))
		ftpf_putpad(' ', param->conv->spacepadlen, param);
	if (fl->sign)
		ftpf_write("-", 1, param);
	else if (param->conv->flags & FTPF_PLUS)
		ftpf_write("+", 1, param);
	else if (param->conv->flags & FTPF_SPACE)
		ftpf_write(" ", 1, param);
	ftpf_putpad('0', param->conv->zeropadlen, param);
	if (type == 'f')
		ftpf_out_float_f(fl, ft_strlen(fl->buf), param);
	else if (type == 'e')
		ftpf_out_float_e(fl, ft_strlen(fl->buf), param);
	else
		ftpf_write(fl->buf, ft_strlen(fl->buf), param);
	if (param->conv->flags & FTPF_MINUS)
		ftpf_putpad(' ', param->conv->spacepadlen, param);
}
