/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 11:57:05 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

size_t	envlen(char **old_env)
{
	size_t	len;

	if (!old_env)
		return (0);
	len = 0;
	while (old_env[len] != NULL)
	{
		len++;
	}
	return (len);
}

char	**envdup_init(char **new_env, char **old_env)
{
	int	i;

	i = 0;
	while (old_env[i])
	{
		new_env[i] = ft_x_strdup(old_env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	init_environ(void)
{
	extern char	**environ;
	static char	**old_env;
	char		**new_env;

	old_env = environ;
	new_env = (char **)ft_x_malloc(sizeof(char *) * (envlen(old_env) + 1), \
		ENVIRON_ERRMSG ": malloc");
	environ = envdup_init(new_env, old_env);
	if (!environ)
		ft_perror_exit(EXIT_FAILURE, ENVIRON_ERRMSG ": malloc");
	return (0);
}
