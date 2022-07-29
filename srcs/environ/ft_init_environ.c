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
#include <stdlib.h>

static void	allocate_env(void)
{
	extern char	**environ;
	char		**tmp;
	char		*env_var;
	char		*content;

	tmp = environ;
	while (*tmp != NULL)
	{
		env_var = ft_strdup(*tmp);
		content = ft_strchr(env_var, '=');
		*content = '\0';
		content++;
		ft_setenv(env_var, content);
		free(env_var);
		tmp++;
	}
}

t_env	**ft_init_environ(void)
{
	static t_env	**env;

	if (env == NULL)
	{
		env = (t_list **)malloc(sizeof(t_env *) * 1);
		if (!env)
		{
			perror("ft_init_environ");
			exit(EXIT_FAILURE);
		}
		allocate_env();
	}
	return (env);
}
