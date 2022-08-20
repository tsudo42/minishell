/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*       add_environ.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

char **add_environ(const char *string)
{
	extern char **environ;
	char	**env_new;
	int i;

	if (!environ)
		return (NULL);
	env_new = (char **)malloc(sizeof(char *) * (envlen() + 2));
	if (!env_new)
		return (NULL);
	i = 0;
	while (environ[i])
	{
		env_new[i] = ft_strdup(environ[i]);
		if (env_new[i++] == NULL)
			return (NULL);
	}
	env_new[i] = ft_strdup(string);
	if (env_new[i++] == NULL)
		return (NULL);
	env_new[i] = NULL;
	free_environ();
	return (env_new);
}
