/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:51:27 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/14 17:52:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exit.h"
#include "ft_put.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	ft_error_exit(int exit_no, const char *msg_prefix, int errno)
{
	const char	*err_msg;
	int			save_errno;

	save_errno = errno;
	if (msg_prefix != NULL)
		ft_putstr_fd(msg_prefix, STDERR_FILENO);
	err_msg = strerror(save_errno);
	if (err_msg != NULL)
		ft_putendl_fd(err_msg, STDERR_FILENO);
	exit(exit_no);
}
