/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/29 13:25:55 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_internal.h"

void	free_environ(void)
{
	extern char	**environ;
	int			i;

	if (!environ)
		return ;
	if (is_init_environ(0) != ENV_INITIALIZED)
		return ;
	i = 0;
	while (environ[i] != NULL)
		free (environ[i++]);
	free (environ);
	environ = NULL;
	return ;
}
