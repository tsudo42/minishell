/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_environ.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static int	ft_envlen(void)
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

char	**ft_init_environ(int plusminus)
{
//	extern char **environ;
	char	**env_new;
	int	len;

	len = ft_envlen();
	env_new = (char **)malloc(sizeof(char **) * len + plusminus + 1);
	if (!env_new)
	{
		perror("ft_init_environ");
		exit(EXIT_FAILURE);
	}
//	free (environ)
//	environ = env_new;
	return (env_new);
}
