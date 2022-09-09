/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/09 13:07:16 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "libft.h"
#include <stdlib.h>

static t_var	*drop_var(t_var *var)
{
	t_var	*next;

	next = var->next;
	free(var->key);
	free(var->value);
	free(var);
	return (next);
}

static int	is_pwd(t_var *var, t_environ *env)
{
	if (ft_strcmp(var->key, "PWD") == 0)
	{
		variable_set("PWD", variable_get("PWD", env), -1, env);
		return (1);
	}
	return (0);
}

/**
 *  This function gets string of variable selected by key if found.
 *  Otherwise, NULL is returned.
 *
 *  Argument key is checked via variable_check_key_format().
 */

int	variable_unset(const char *key, t_environ *env)
{
	t_var	*var;

	if (variable_check_key_format(key) != 0)
		return (-1);
	var = env->vars;
	if (var->key != NULL && ft_strcmp(var->key, key) == 0)
	{
		if (!is_pwd(var, env))
			env->vars = drop_var(var);
		return (0);
	}
	while (var->next != NULL)
	{
		if (var->next->key != NULL && ft_strcmp(var->next->key, key) == 0)
		{
			if (!is_pwd(var->next, env))
				var->next = drop_var(var->next);
			return (0);
		}
		var = var->next;
	}
	return (0);
}
