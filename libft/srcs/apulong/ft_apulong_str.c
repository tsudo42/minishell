/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apulong_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 09:13:34 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:22:19 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_apulong.h"
#include "ft_mem.h"

/* 20 * FT_APULONG_SIZE <= \log_{10} (2^{64 * FT_APULONG_SIZE} - 1) */
const char	*ft_apulong_str(t_ft_apulong a, char *str)
{
	t_ft_apulong	tmp;
	t_ft_apulong	zero;
	unsigned long	mod;
	char			buf[20 * FT_APULONG_SIZE + 1];
	int				i;

	i = 0;
	zero = ft_apulong_val(0);
	tmp = ft_apulong_cpy(a);
	while (ft_apulong_cmp(tmp, zero) != 0)
	{
		tmp = ft_apulong_div10(tmp, &mod);
		i++;
		buf[20 * FT_APULONG_SIZE + 1 - i] = mod + '0';
	}
	if (i == 0)
	{
		i++;
		buf[20 * FT_APULONG_SIZE + 1 - i] = '0';
	}
	ft_memcpy(str, &(buf[20 * FT_APULONG_SIZE + 1 - i]), i);
	str[i] = '\0';
	return (str);
}
