/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrapped_malloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:50:51 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/14 15:56:33 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exit.h"
#include <stdlib.h>

void	*ft_wrapped_malloc(size_t size, int exit_no, const char *err_msg)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		ft_exit(exit_no, err_msg);
	return (ptr);
}
