/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 17:17:06 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_internal.h"

static int	*stored_status(void)
{
	static int	status;

	return (&status);
}

/**
 *  This function stores the argument as exit status.
 */
void	set_exit_status(int status)
{
	(*stored_status()) = status;
}

/**
 *  This function returns the stored exit status.
 */
int	get_exit_status(void)
{
	return (*(stored_status()));
}

/**
 *  This function returns the string representation of the stored exit status.
 *  This function returns NULL when malloc(3) fails.
 */
const char	*get_exit_status_str(void)
{
	static char	*alloced_str;
	int			status;

	status = get_exit_status();
	if (status == 0)
		return ("0");
	if (status == 1)
		return ("1");
	if (alloced_str == NULL)
	{
		alloced_str = malloc(sizeof(char) * 16);
		if (alloced_str == NULL)
		{
			perror(ENVIRON_ERRMSG ": malloc");
			return (NULL);
		}
	}
	return (ft_itoa_buf(status, alloced_str, 16));
}
