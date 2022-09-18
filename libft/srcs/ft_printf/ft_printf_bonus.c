/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:39:16 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/08 17:37:16 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"
#include "ft_mem.h"

static void	ftpf_convert(t_ftpf *param)
{
	t_ftpf_conv	conv;

	ft_memset(&conv, 0, sizeof(t_ftpf_conv));
	param->conv = &conv;
	ftpf_option(param);
	ftpf_length(param);
	ftpf_type(param);
}

static void	ftpf_parse(t_ftpf *param)
{
	while (*(param->fmt) != '\0')
	{
		if (*(param->fmt) == '%')
		{
			param->fmt++;
			if (*(param->fmt) == '\0')
				break ;
			ftpf_convert(param);
		}
		else
		{
			ftpf_write(param->fmt, 1, param);
			param->fmt++;
		}
	}
}

int	ft_printf_bonus(const char *fmt, ...)
{
	t_ftpf	param;

	param.fd = 1;
	param.fmt = fmt;
	va_start(param.args, fmt);
	param.ret = 0;
	param.errnum = 0;
	ftpf_parse(&param);
	va_end(param.args);
	if (param.errnum != 0)
	{
		errno = param.errnum;
		return (-1);
	}
	return (param.ret);
}
