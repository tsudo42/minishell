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
	char	**env_new;
	int i;
	extern char **environ;

	env_new = (char **)malloc(sizeof(char *) * (envlen() + 2));
	if (!env_new)
	{
		free_environ();
		perror("add_environ");
		exit(EXIT_FAILURE);
	}	
	i = 0;
	if (!environ)
		return NULL;
	while (environ[i])
	{
		env_new[i] = ft_strdup(environ[i]);
		i++;
	}
	env_new[i++] = ft_strdup(string);
//	env_new[i] = ft_strdup("");
	env_new[i] = NULL;
	free_environ();
	environ = NULL;
	return (env_new);
}
