/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/25 19:53:51 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

void free_environ(void)
{
	extern char **environ;
	int i;

	if (!environ)
		return ;
	i = 0;
	while (environ[i] != NULL)
		free (environ[i++]);
	free (environ);
	environ = NULL;
	return ;
}
