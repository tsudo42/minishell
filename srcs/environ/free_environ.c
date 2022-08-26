/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/26 22:02:23 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

void	free_environ(void)
{
	extern char	**environ;
	int			i;

	if (!environ)
		return ;
	i = 0;
	while (environ[i] != NULL)
		free (environ[i++]);
	free (environ);
	environ = NULL;
	return ;
}

void	free_env_new(char **env_new, int i)
{
	int	j;

	if (!env_new)
		return ;
	j = 0;
	while (j < i - 1)
		free(env_new[j++]);
	free (env_new);
	return ;
}
