/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/04 21:30:52 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_internal.h"

static char	**init_environ(void)
{
	extern char	**environ;
	char		**new_env;
	int			i;

	if (!environ)
	{
		perror(ENVIRON_ERRMSG ": environ");
		exit(EXIT_FAILURE);
	}
	new_env = (char **)ft_x_malloc(sizeof(char *) * (envlen(environ) + 1), \
		ENVIRON_ERRMSG ": malloc");
	i = 0;
	while (environ[i])
	{
		new_env[i] = ft_x_strdup(environ[i], ENVIRON_ERRMSG);
		i++;
	}
	new_env[i] = NULL;
	is_init_environ(1);
	return (new_env);
}

char	**add_environ(const char *string)
{
	extern char	**environ;
	char		**new_env;
	int			i;

	if (!environ)
	{
		perror(ENVIRON_ERRMSG ": environ");
		exit(EXIT_FAILURE);
	}
	new_env = (char **)ft_x_malloc(sizeof(char *) * (envlen(environ) + 2), \
		ENVIRON_ERRMSG ": malloc");
	i = 0;
	while (environ[i])
	{
		new_env[i] = ft_x_strdup(environ[i], ENVIRON_ERRMSG);
		i++;
	}
	new_env[i++] = ft_x_strdup(string, ENVIRON_ERRMSG);
	new_env[i] = NULL;
	free_environ();
	is_init_environ(1);
	return (new_env);
}

static int	find_string(const char *string)
{
	extern char	**environ;
	char		*name;
	int			location;
	int			len;
	char		*value;

	value = ft_strchr(string, '=');
	len = value - string;
	if (value > string && *(value - 1) == '+')
		len--;
	name = ft_strndup(string, len);
	location = 0;
	while (environ[location])
	{
		if (ft_strncmp(environ[location], name, len) == 0 \
				&& environ[location][len] == '=')
		{
			free (name);
			return (location);
		}
		location++;
	}
	free (name);
	return (-1);
}

static int	change_content(const char *string, int location)
{
	extern char	**environ;
	char		*tmp;
	int			len;

	if (is_init_environ(0) != 1)
		environ = init_environ();
	tmp = ft_strchr(string, '=');
	len = tmp - string;
	if (tmp > string && string[len - 1] == '+')
	{
		tmp = ft_strjoin(environ[location], (ft_strchr(string, '=')) + 1);
		if (!tmp)
		{
			perror(ENVIRON_ERRMSG ": environ");
			exit(EXIT_FAILURE);
		}
		free (environ[location]);
		environ[location] = tmp;
	}
	else
	{
		free (environ[location]);
		environ[location] = ft_x_strdup(string, ENVIRON_ERRMSG);
	}
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
	return (0);
}
