/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_option_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:03:27 by tsudo             #+#    #+#             */
/*   Updated: 2022/02/04 18:13:48 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"
#include "ft_char.h"
#include "ft_int.h"
#include "ft_string.h"

static void	ftpf_option_minfield(t_ftpf *param)
{
	if (ft_numstrcmp(param->fmt, "2147483647") <= 0)
		param->conv->minfield = ft_atoi(param->fmt);
	else
		param->conv->minfield = 2147483647;
	while (ft_isdigit(*(param->fmt)))
		param->fmt++;
}

static void	ftpf_option_precision(t_ftpf *param)
{
	if (ft_numstrcmp(param->fmt, "2147483647") <= 0)
		param->conv->precision = ft_atoi(param->fmt);
	else
		param->conv->precision = 2147483647;
	while (ft_isdigit(*(param->fmt)))
		param->fmt++;
}

static void	ftpf_option_flags(t_ftpf *param)
{
	size_t	offset;

	offset = 1;
	if (*(param->fmt) == '-')
		param->conv->flags |= FTPF_MINUS;
	else if (*(param->fmt) == '0')
		param->conv->flags |= FTPF_ZERO;
	else if (*(param->fmt) == '.')
	{
		param->conv->flags |= FTPF_DOT;
		param->fmt++;
		offset = 0;
		ftpf_option_precision(param);
	}
	else if (*(param->fmt) == '#')
		param->conv->flags |= FTPF_HASH;
	else if (*(param->fmt) == ' ')
		param->conv->flags |= FTPF_SPACE;
	else if (*(param->fmt) == '+')
		param->conv->flags |= FTPF_PLUS;
	else if (*(param->fmt) == '\'')
		param->conv->flags |= FTPF_QUOTE;
	else
		offset = 0;
	param->fmt += offset;
}

void	ftpf_option(t_ftpf *param)
{
	while (*(param->fmt) != '\0')
	{
		if (ft_strchr("-0.'", *(param->fmt)) != NULL)
			ftpf_option_flags(param);
		else if (ft_strchr("# +", *(param->fmt)) != NULL)
			ftpf_option_flags(param);
		else if (ft_isdigit(*(param->fmt)))
			ftpf_option_minfield(param);
		else
			break ;
	}
}
