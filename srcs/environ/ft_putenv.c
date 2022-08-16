/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static int find_string(const char *string)
{
	extern char **environ;
	int i;
	int len;

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

int change_content(const char *string, int location)
{
	extern char **environ;

	free(environ[location]);
	environ[location] = NULL;
	environ[location] = ft_strdup(string);
	return (0);
}

int	ft_putenv(const char *string)
{
	extern char	**environ;
	char **env_new;
	int location;

	if ((location = find_string(string)) != -1)
		return (change_content(string, location));
	env_new = add_environ(string);
	if (!env_new)
		return (-1);
	environ = env_new;
	return (0);
}
