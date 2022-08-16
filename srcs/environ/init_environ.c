/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*      init_environ.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int	envlen(void)
{
	extern char **environ;
	char **tmp;
	int len;

	tmp = environ;
	len = 0;
	while (*tmp)
	{
		tmp++;
		len++;
	}
	return (len);
}

void	init_environ(void)
{
	char	**env_new;
	extern char **environ;
	int i;

	env_new = (char **)malloc(sizeof(char *) * (envlen() + 1));
	if (!env_new)
	{
		perror("init_environ");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (environ[i])
	{
		env_new[i] = ft_strdup(environ[i]);
		i++;
	}
	env_new[i] = ft_strdup("");
	environ = env_new;
	return ;
}
