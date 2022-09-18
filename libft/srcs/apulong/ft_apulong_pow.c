/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apulong_pow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:45:22 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:22:14 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_apulong.h"

t_ft_apulong	ft_apulong_pow(unsigned long a, unsigned int p)
{
	t_ft_apulong	r;
	unsigned int	i;

	r = ft_apulong_val(1);
	i = 0;
	while (i < p)
	{
		r = ft_apulong_mul(r, a);
		i++;
	}
	return (r);
}
