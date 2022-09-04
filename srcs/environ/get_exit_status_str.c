/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_status_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 17:17:06 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_internal.h"

/**
 *  This function returns the string representation of the stored exit status.
 *  Returned string from this function should not be freed.
 */
const char	*get_exit_status_str(t_environ *env)
{
	static char	str_buf[16];

	if (env->exit_status == 0)
		return ("0");
	if (env->exit_status == 1)
		return ("1");
	return (ft_itoa_buf(env->exit_status, str_buf, 16));
}
