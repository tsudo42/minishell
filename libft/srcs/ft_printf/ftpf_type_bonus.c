/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_type_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 08:55:40 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/08 16:49:57 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"
#include "ft_string.h"

void	ftpf_type(t_ftpf *param)
{
	if (*(param->fmt) == '\0')
		return ;
	else if (ft_strchr("cC%", *(param->fmt)) != NULL)
		ftpf_out_char(param);
	else if (ft_strchr("sS", *(param->fmt)) != NULL)
		ftpf_out_string(param);
	else if (ft_strchr("di", *(param->fmt)) != NULL)
		ftpf_out_signed(param);
	else if (ft_strchr("uoxXp", *(param->fmt)) != NULL)
		ftpf_out_unsigned(param);
	else if (ft_strchr("efgEFG", *(param->fmt)) != NULL)
		ftpf_out_float(param);
	else if (ft_strchr("aA", *(param->fmt)) != NULL)
		ftpf_out_hexfloat(param);
}
