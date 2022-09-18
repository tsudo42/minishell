/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apulong_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:45:31 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:21:54 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_apulong.h"

t_ft_apulong	ft_apulong_add(t_ft_apulong a, t_ft_apulong b)
{
	t_ft_apulong	r;
	int				i;
	unsigned long	prev;
	unsigned long	ovf;

	r = ft_apulong_cpy(a);
	i = 0;
	ovf = 0;
	while (i < r.size && i < b.size)
	{
		prev = r.l[i];
		r.l[i] += b.l[i] + ovf;
		ovf = 0;
		if (r.l[i] < prev)
			ovf = 1;
		i++;
	}
	if (i < r.size && ovf == 1)
		r.l[i] += ovf;
	return (r);
}
