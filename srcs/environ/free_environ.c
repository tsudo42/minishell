/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/29 13:11:03 by hos              ###   ########.fr       */
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
	printf("free_environ(before): %p\n\n", environ);
	i = 0;
	while (environ[i] != NULL)
		free (environ[i++]);
	printf("free_environ(after): %p\n\n", environ);
	free (environ);
	environ = NULL;
	return ;
}
