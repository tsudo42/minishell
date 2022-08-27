/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_environ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 17:17:37 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_internal.h"

char	**add_environ(const char *string)
{
	extern char	**environ;
	char		**new_env;
	int			i;

	if (!environ)
		return (NULL);
	new_env = (char **)malloc(sizeof(char *) * (envlen(environ) + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (environ[i])
	{
		new_env[i] = ft_strdup(environ[i]);
		if (new_env[i++] == NULL)
			return (NULL);
	}
	new_env[i] = ft_strdup(string);
	if (new_env[i++] == NULL)
		return (NULL);
	new_env[i] = NULL;
	free_environ();
	return (new_env);
}
