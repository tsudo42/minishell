/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_environ.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int	ft_envlen(void)
{
	extern char **environ;
	char **tmp;

	int i;

	tmp = environ;
	i = 0;
	while (*tmp)
	{
		tmp++;
		i++;
	}
	return (i);
}

void	ft_init_environ(void)
{
	extern char **environ;
	char	**env_new;
	static int initialized;
	int i;

	if (initialized != 0)
		return ;
	initialized = 1;
	env_new = (char **)malloc(sizeof(char **) * (ft_envlen() + 1));
	if (!env_new)
	{
		perror("ft_init_environ");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (environ[i])
	{
		env_new[i] = environ[i];
		i++;
	}
	env_new[i] = NULL;
	environ = env_new;
}
