/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int	ft_putenv(const char *string)
{
	char	*content;

	//	if (ft_strcmp("?", name) == 0)
//		return (ft_itoa(*exit_status()));
	content = ft_getenv(string);
	if (!content)
		return (-1);
	ft_putstr_fd(content, STDOUT_FILENO);
	return (0);
}
