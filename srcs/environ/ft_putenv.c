/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/29 13:11:56 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_internal.h"

char	**add_environ(const char *string)
{
	extern char	**environ;
	char		**new_env;
	int			i;

	if (!environ)
		ft_perror_exit(EXIT_FAILURE, ENVIRON_ERRMSG ": environ");
	new_env = (char **)ft_x_malloc(sizeof(char *) * (envlen(environ) + 2), \
		ENVIRON_ERRMSG ": malloc");
	i = 0;
	while (environ[i])
	{
		new_env[i] = ft_x_strdup(environ[i]);
		i++;
	}
	new_env[i++] = ft_x_strdup(string);
	new_env[i] = NULL;
	free_environ();
	return (new_env);
}

static int	find_string(const char *string)
{
	extern char	**environ;
	int			i;
	int			len;

	len = ft_strchr(string, '=') - string;
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], string, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	change_content(const char *string, int location)
{
	extern char	**environ;

	free (environ[location]);
	environ[location] = NULL;
	environ[location] = ft_x_strdup(string);
	return (0);
}

int	ft_putenv(const char *string)
{
	extern char	**environ;
	int			location;

	location = find_string(string);
	if (location != -1)
		return (change_content(string, location));
	environ = add_environ(string);
	is_init_environ(1);
	return (0);
}
