/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 17:17:37 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_internal.h"

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
	environ[location] = ft_strdup(string);
	if (environ[location] == NULL)
		ft_perror_exit(EXIT_FAILURE, ENVIRON_ERRMSG ": malloc");
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
	if (!environ)
	{
		free_environ();
		ft_perror_exit(EXIT_FAILURE, ENVIRON_ERRMSG ": malloc");
	}
	return (0);
}
