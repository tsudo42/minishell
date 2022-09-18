/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrapped_puts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:50:51 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/15 13:24:32 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exit.h"
#include <limits.h>
#include <unistd.h>

int	ft_wrapped_puts(const char *s, int exit_no, const char *err_msg)
{
	const char	*nul = "(null)";
	size_t		len;
	int			tmp;
	int			ret;

	if (s == NULL)
		s = nul;
	ret = 0;
	len = 0;
	while (s[len] != '\0')
		len++;
	while (len > INT_MAX)
	{
		tmp = write(1, s, INT_MAX);
		if (tmp <= 0)
			ft_exit(exit_no, err_msg);
		s += tmp;
		len -= tmp;
		ret += tmp;
	}
	tmp = write(1, s, len);
	if (tmp < (int)len || write(1, "\n", 1) < 1)
		ft_exit(exit_no, err_msg);
	return (ret + tmp);
}
