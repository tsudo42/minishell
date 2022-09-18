/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apulong_cpy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:43:54 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 16:22:04 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_apulong.h"

t_ft_apulong	ft_apulong_cpy(t_ft_apulong a)
{
	t_ft_apulong	r;
	int				i;

	r.size = a.size;
	i = 0;
	while (i < a.size)
	{
		r.l[i] = a.l[i];
		i++;
	}
	return (r);
}
