/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_float_get_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 08:01:27 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 17:47:39 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"
#include "ft_string.h"
#include "ft_mem.h"

static void	ftpf_dbl_getdata_helper(t_ftpf_float *fl, int exp)
{
	fl->e0 = ft_strlen(fl->buf) - 1;
	if (52 - exp > 0)
		fl->e0 -= (52 - exp);
	if (fl->buf[0] == '0')
		fl->e0 = 0;
}

int	ftpf_dbl_getdata(t_ftpf_float *fl, double d)
{
	unsigned long	tmp;
	unsigned long	frac;
	long			exp;

	ft_memcpy(&tmp, &d, sizeof(double));
	fl->sign = ((tmp & (ULONG_MAX ^ (ULONG_MAX >> 1))) != 0);
	exp = (((tmp << 1) >> 1) >> 52) - 0x3ff;
	frac = (tmp & ((0x1UL << 52) - 1UL));
	fl->e0 = (frac == 0);
	if ((((tmp << 1) >> 1) >> 52) == ((ULONG_MAX << 1) >> 1) >> 52)
		return (1);
	if (tmp >> 52)
		frac |= 0x1UL << 52;
	else
		exp = 1 - 0x3ff;
	if (exp - 52 >= 0)
		fl->ap = ft_apulong_pow(2, exp - 52);
	else
		fl->ap = ft_apulong_pow(5, 52 - exp);
	fl->ap = ft_apulong_mul(fl->ap, frac);
	ft_apulong_str(fl->ap, fl->buf);
	ftpf_dbl_getdata_helper(fl, exp);
	return (0);
}

void	ftpf_dbl_other(t_ftpf_float *fl, t_ftpf *param)
{
	if (fl->e0)
	{
		if ('A' <= *(param->fmt) && *(param->fmt) <= 'Z')
			ft_strlcpy(fl->buf, "INF", 10);
		else
			ft_strlcpy(fl->buf, "inf", 10);
	}
	else
	{
		if ('A' <= *(param->fmt) && *(param->fmt) <= 'Z')
			ft_strlcpy(fl->buf, "NAN", 10);
		else
			ft_strlcpy(fl->buf, "nan", 10);
		fl->sign = 0;
		param->conv->flags &= ~(FTPF_PLUS | FTPF_SPACE);
	}
}
