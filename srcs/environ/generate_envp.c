/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/29 13:35:08 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "environ_internal.h"
#include "libft.h"
#include <stdio.h>

static char	**alloc_envp(t_environ *env)
{
	char	**envp;
	t_var	*var;
	size_t	len;

	len = 0;
	var = env->vars;
	while (var != NULL)
	{
		if (var->value != NULL && var->is_exported)
			len++;
		var = var->next;
	}
	envp = malloc(sizeof(char *) * (len + 1));
	if (envp == NULL)
	{
		perror(ENVIRON_ERRMSG ": malloc");
		exit(1);
	}
	return (envp);
}

/**
 *  This function generates the array of environ variables,
 *  which can be passed to the 3rd argument of execve.
 */
char	**generate_envp(t_environ *env)
{
	char	**envp;
	size_t	i;
	t_var	*var;

	envp = alloc_envp(env);
	i = 0;
	var = env->vars;
	while (var != NULL)
	{
		if (var->value != NULL && var->is_exported)
		{
			envp[i] = ft_strjoin3(var->key, "=", var->value);
			if (envp[i] == NULL)
			{
				perror(ENVIRON_ERRMSG ": malloc");
				exit(1);
			}
			i++;
		}
		var = var->next;
	}
	envp[i] = NULL;
	return (envp);
}
