/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_float_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 06:43:52 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 17:47:46 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"
#include "ft_string.h"

/* ____<buf[0]><buf[1]>...<buf[e0]><DOT><buf[e0+1]>...<buf[e0+precision]>____ */
/* <buf> := <buf[0]><buf[1]><buf[2]><buf[3]>...<buf[len-1]><buf[len]=='\0'>   */
/* <integer> := <buf[0]><buf[1]>...<buf[e0]>                                  */
/* <decimal> := <buf[e0+1]><buf[e0+2]><buf[e0+3]>...<buf[e0+precision]>       */
void	ftpf_trimdata(t_ftpf_float *fl, int e0, t_ftpf *param)
{
	int	len;

	len = ft_strlen(fl->buf);
	if (param->conv->precision < 0)
		param->conv->precision = 0;
	if (e0 + param->conv->precision + 1 > 0 && \
		e0 + param->conv->precision + 1 < len - 1)
	{
		if (fl->buf[e0 + param->conv->precision + 1] >= '5')
		{
			fl->ap = ft_apulong_add(fl->ap, \
			ft_apulong_pow(10, len - 1 - (param->conv->precision + e0)));
			ft_apulong_str(fl->ap, fl->buf);
			if (len < (int)ft_strlen(fl->buf))
			{
				fl->e0++;
				e0++;
			}
		}
	}
}

/* head_e : fl->e0           means the exponent of fl->buf[0]     */
/* tail_e : fl->e0 - len + 1 means the exponent of fl->buf[len-1] */
static void	ftpf_out_float_f_helper(t_ftpf_float *fl, int len, t_ftpf *param)
{
	int	head_e;
	int	tail_e;
	int	prec_e;

	head_e = fl->e0;
	tail_e = fl->e0 - len + 1;
	prec_e = -param->conv->precision;
	if (param->conv->precision < 0)
		param->conv->precision = 0;
	if (0 > head_e)
		ftpf_write("0", 1, param);
	else if (tail_e >= 0)
	{
		ftpf_write(fl->buf, len, param);
		ftpf_putpad('0', tail_e, param);
	}
	else
		ftpf_write(fl->buf, head_e + 1, param);
	if (0 > prec_e || param->conv->flags & FTPF_HASH)
		ftpf_write(".", 1, param);
}

void	ftpf_out_float_f(t_ftpf_float *fl, int len, t_ftpf *param)
{
	int	head_e;
	int	tail_e;
	int	prec_e;

	head_e = fl->e0;
	tail_e = fl->e0 - len + 1;
	prec_e = -param->conv->precision;
	ftpf_out_float_f_helper(fl, len, param);
	if (-1 >= head_e && head_e >= prec_e)
	{
		ftpf_putpad('0', -1 - head_e, param);
		if (tail_e >= prec_e)
			ftpf_write(fl->buf, len, param);
		else
			ftpf_write(fl->buf, -prec_e - (-1 - head_e), param);
	}
	else if (0 > tail_e && tail_e >= prec_e)
		ftpf_write(fl->buf + (head_e - (-1)), -tail_e, param);
	else if (head_e >= 0 && prec_e > tail_e)
		ftpf_write(fl->buf + (head_e - (-1)), -prec_e, param);
	if (tail_e >= 0 || prec_e > head_e)
		ftpf_putpad('0', -prec_e, param);
	else if (tail_e > prec_e)
		ftpf_putpad('0', tail_e - prec_e, param);
}

/* assert( len > 0 ) */
void	ftpf_out_float_e(t_ftpf_float *fl, int len, t_ftpf *param)
{
	ftpf_write(fl->buf, 1, param);
	if (param->conv->precision > 0 || param->conv->flags & FTPF_HASH)
		ftpf_write(".", 1, param);
	if (param->conv->precision > 0)
	{
		if (param->conv->precision < (len - 1))
			ftpf_write(fl->buf + 1, param->conv->precision, param);
		else
		{
			ftpf_write(fl->buf + 1, (len - 1), param);
			if (param->conv->precision - (len - 1) > 0)
				ftpf_putpad('0', param->conv->precision - (len - 1), param);
		}
	}
	if ('A' <= *(param->fmt) && *(param->fmt) <= 'Z')
		ftpf_write("E", 1, param);
	else
		ftpf_write("e", 1, param);
	if (fl->e0 >= 0)
		ftpf_write("+", 1, param);
	else
		ftpf_write("-", 1, param);
	if (-10 < fl->e0 && fl->e0 < 10)
		ftpf_write("0", 1, param);
	ftpf_putnbr(fl->e0, 10, 0, param);
}
