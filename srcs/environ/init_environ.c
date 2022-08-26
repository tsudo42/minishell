/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 08:47:04 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int	envlen(void)
{
	extern char	**environ;
	char		**tmp;
	int			len;

	if (!environ)
		return (0);
	tmp = environ;
	len = 0;
	while (*tmp)
	{
		tmp++;
		len++;
	}
	return (len);
}

char	**envdup_init(char **env_new)
{
	extern char	**environ;
	int			i;

	if (!environ)
		return (NULL);
	i = 0;
	while (environ[i])
	{
		env_new[i] = ft_x_strdup(environ[i]);
		i++;
		//	env_new[i] = ft_strdup(environ[i]);
/*		if (env_new[i++] == NULL)
		{
			free_env_new(env_new, i);
			return (NULL);
		}
*/	}
	env_new[i] = NULL;
	return (env_new);
}

int	init_environ(void)
{
	char		**env_new;
	extern char	**environ;

	if (!environ)
		return (0);
	env_new = (char **)ft_x_malloc(sizeof(char *) * (envlen() + 1),\
	ENVIRON_ERRMSG ": malloc");
/*
 	env_new = (char **)malloc(sizeof(char *) * (envlen() + 1));
	if (!env_new)
		ft_perror_exit(EXIT_FAILURE, ENV_ERRMSG ": malloc");
*/
	environ = envdup_init(env_new);
	if (!environ)
		ft_perror_exit(EXIT_FAILURE, ENV_ERRMSG ": malloc");
	return (0);
}
