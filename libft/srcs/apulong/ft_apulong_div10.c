/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apulong_div10.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:45:05 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 17:51:15 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_apulong.h"

/* assume ULONG_MAX + 1 == 18446744073709551616  */
/* assume (ULONG_MAX + 1) / 10 == 1844674407370955161UL */
/* assume (ULONG_MAX + 1) % 10 == 6 */
/* m * (ULONG_MAX + 1) + n % 10 == (m * 6 + n % 10) % 10 */
/* m * (ULONG_MAX + 1) + n / 10 == m * 1844674407370955161 + n / 10
                                 + (m * 6 + n % 10) / 10 */
t_ft_apulong	ft_apulong_div10(t_ft_apulong a, unsigned long *m)
{
	t_ft_apulong	r;
	int				i;
	unsigned long	div;
	unsigned long	mod;
	unsigned long	tmp;

	i = a.size - 1;
	div = 0;
	mod = 0;
	r.size = a.size;
	while (i >= 0)
	{
		tmp = mod * 6 + (a.l[i] % 10);
		div = (mod * 1844674407370955161UL) + a.l[i] / 10 + tmp / 10;
		mod = tmp % 10;
		r.l[i] = div;
		i--;
	}
	*m = mod;
	return (r);
}
