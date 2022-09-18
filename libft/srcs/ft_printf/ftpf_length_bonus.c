/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_length_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 09:38:56 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 17:47:48 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"

static void	ftpf_length_2(t_ftpf *param);

void	ftpf_length(t_ftpf *param)
{
	if (*(param->fmt) == 'h')
	{
		param->fmt++;
		if (*(param->fmt) == 'h')
		{
			param->fmt++;
			param->conv->length = FTPF_CHAR;
		}
		else
			param->conv->length = FTPF_SHORT;
	}
	else if (*(param->fmt) == 'l')
	{
		param->fmt++;
		if (*(param->fmt) == 'l')
		{
			param->fmt++;
			param->conv->length = FTPF_LLONG;
		}
		else
			param->conv->length = FTPF_LONG;
	}
	else
		ftpf_length_2(param);
}

static void	ftpf_length_2(t_ftpf *param)
{
	if (*(param->fmt) == 'L')
	{
		param->fmt++;
		param->conv->length = FTPF_LDOUBLE;
	}
	else if (*(param->fmt) == 'z')
	{
		param->fmt++;
		param->conv->length = FTPF_SIZE_T;
	}
	else if (*(param->fmt) == 'j')
	{
		param->fmt++;
		param->conv->length = FTPF_INTMAX_T;
	}
	else if (*(param->fmt) == 't')
	{
		param->fmt++;
		param->conv->length = FTPF_PTRDIFF_T;
	}
}
