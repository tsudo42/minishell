/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include <stdlib.h>

//return value can be void?
int	ft_setenv(const char *env_var, const char *content, int overwrite)
{
	t_env	**env;
	t_env	*tmp;
	t_env	*tmp2;

	(void)overwrite;
	env = ft_init_environ();
	tmp = *env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->env_var, env_var) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strdup(content);
			return (0);
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	tmp2 = (t_env *)malloc(sizeof(t_env) * 1);
	tmp2->env_var = ft_strdup(env_var);
	tmp2->content = ft_strdup(content);
	tmp->next = tmp2;
	return (0);
}

