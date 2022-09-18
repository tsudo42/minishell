/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apulong_val.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:43:31 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:22:22 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_apulong.h"

t_ft_apulong	ft_apulong_val(unsigned long val)
{
	t_ft_apulong	a;
	int				i;

	a.size = FT_APULONG_SIZE;
	a.l[0] = val;
	i = 1;
	while (i < a.size)
	{
		a.l[i] = 0;
		i++;
	}
	return (a);
}
