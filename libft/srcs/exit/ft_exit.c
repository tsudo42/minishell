/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
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

void	ft_exit(int exit_no, const char *err_msg)
{
	if (err_msg != NULL)
		ft_putendl_fd(err_msg, 2);
	exit(exit_no);
}
