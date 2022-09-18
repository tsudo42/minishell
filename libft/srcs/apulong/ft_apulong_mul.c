/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apulong_mul.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:45:14 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:22:12 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_apulong.h"

t_ft_apulong	ft_apulong_mul(t_ft_apulong a, unsigned long b)
{
	t_ft_apulong	r;
	unsigned long	mask;

	r = ft_apulong_val(0);
	mask = ULONG_MAX ^ (ULONG_MAX >> 1);
	while (!(b & mask) && mask)
		mask = mask >> 1;
	while (mask)
	{
		r = ft_apulong_add(r, r);
		if (b & mask)
			r = ft_apulong_add(r, a);
		mask /= 2;
	}
	return (r);
}
