/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "builtin.h"
#include <stdlib.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
			return (-1);
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			break ;
		s1++;
		s2++;
		if (!s1 || !s2)
			return (-1);
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_getenv(const char *name)
{
	t_env	**env;
	t_env	*tmp;

	if (ft_strcmp("?", name) == 0)
		return (ft_itoa(g_status));
	env = ft_init_environ();
	tmp = *env;
	while (tmp != NULL)
	{
		if (tmp->env_var != NULL && ft_strcmp(tmp->env_var, name) == 0)
			return (ft_strdup(tmp>content));
		tmp = tmp->next;
	}
	return (NULL);
}
