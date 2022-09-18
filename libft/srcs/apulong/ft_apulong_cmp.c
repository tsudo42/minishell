/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apulong_cmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:44:05 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:22:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_apulong.h"

int	ft_apulong_cmp(t_ft_apulong a, t_ft_apulong b)
{
	int				i;
	unsigned long	a_tmp;
	unsigned long	b_tmp;

	i = a.size - 1;
	a_tmp = 0;
	b_tmp = 0;
	while (i >= 0)
	{
		if (i <= a.size)
			a_tmp = a.l[i];
		if (i <= b.size)
			b_tmp = b.l[i];
		if (a_tmp != b_tmp)
			break ;
		i--;
	}
	if (a_tmp > b_tmp)
		return (1);
	else if (a_tmp < b_tmp)
		return (-1);
	return (0);
}
