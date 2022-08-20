/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

char *env_strjoin(const char *name, const char *value)
{
	char *res;
	int len1;
	int	len2;
	int i;
	
	if (!name || !value)
		return (NULL);
	len1 = ft_strlen(name);
	len2 = ft_strlen(value);
	res = (char *)malloc(sizeof(char) * (len1 + len2 + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (*name)
		res[i++] = *(name++);
	res[i++] = '=';
	while (*value)
		res[i++] = *(value++);
	res[i] = '\0';
	return (res);
}

int find_name(const char *name)
{
	extern char **environ;
	int i;
	int len;
	int len_env;

	i = 0;
	len = ft_strlen(name);
	while (environ[i])
	{
		len_env = ft_strlen(environ[i]);
		if (len_env < len)
		{
			i++;
			continue ;
		}
		if (ft_strncmp(environ[i], name, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int setenv_overwrite(const char *name, const char *value, int len)
{
	extern char **environ;

	free (environ[len]);
	environ[len] = NULL;
	environ[len] = env_strjoin(name, value);
	if (!environ[len])
	{
		free_environ();
		ft_perror_exit(EXIT_FAILURE, ENV_ERRMSG ": malloc");
	}
	return (0);
}

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	extern char	**environ;
	char *str;
	int len;

	init_environ();
	if ((len = find_name(name)) != -1)
	{
		if (overwrite != 0)
			return (setenv_overwrite(name, value, len));
		return (0);
	}
	str = env_strjoin(name, value);
	if (!str)
	{
		free_environ();
		ft_perror_exit(EXIT_FAILURE, ENV_ERRMSG ": malloc");
	}
	environ = add_environ(str);
	if (!environ)
	{
		free_environ();
		ft_perror_exit(EXIT_FAILURE, ENV_ERRMSG ": environ");
	}
	free(str);
	return (0);
}
