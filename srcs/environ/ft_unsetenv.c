/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static int find_name(const char *name)
{
	extern char **environ;
	int i;
	int len;

	i = 0;
	len = ft_strlen(name);
	while (environ[i])
	{
		if (ft_strncmp(environ[i], name, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_unsetenv(const char *name)
{
	extern char **environ;
	char **tmp;
	int skip;
	int i;
	int j;

	init_environ();
	if ((skip = find_name(name)) == -1)
		return (-1);
	tmp = (char **)malloc(sizeof(char **) * envlen());
	if (!tmp)
		return (-1);
	i = 0;
	j = 0;
	while (environ[j])
	{
		if (i == skip)
			j++;
		if (environ[j])
			tmp[i++] = environ[j++];
	}
	tmp[i] = NULL;
	free (environ);
	environ = tmp;
	return (0);
}
