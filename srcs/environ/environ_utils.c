/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_init_environ.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/29 13:15:10 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_internal.h"

size_t	envlen(char **envp)
{
	size_t	len;

	if (!envp)
		return (0);
	len = 0;
	while (envp[len] != NULL)
	{
		len++;
	}
	return (len);
}

int is_init_environ(int activation)
{
	static int initialized;

	if (activation == 1)
		initialized = ENV_INITIALIZED;
	return (initialized);
}
