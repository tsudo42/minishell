/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/09 13:08:25 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static void	variable_update(t_var *var, const char *value, int export)
{
	char	*new_value;

	if (value != NULL)
	{
		new_value = ft_strdup(value);
		if (new_value == NULL)
		{
			perror(ENVIRON_ERRMSG ": malloc");
			exit(1);
		}
		free(var->value);
		var->value = new_value;
	}
	else
		var->value = NULL;
	if (export == -1)
		var->is_exported = 0;
	else if (export)
		var->is_exported = export;
}

/**
 *  This function sets key-value variable.
 *
 *  If value argument is NULL, value of variable will not be updated
 *  but whether the variable is exported can be updated.
 *
 *  Environment variables are stored when export is true.
 *  Internal variables are stored when export is false.
 *
 *  When updating an internal variable with is_exp == true,
 *  the variable will be environment variable.
 *  Environment variable can be updated with is_exp == false.
 *
 *  key is checked via variable_check_key_format().
 *  This function exits with 1 when malloc(3) fails.
 */
int
	variable_set(const char *key, const char *value, int export, t_environ *env)
{
	t_var	*var;

	if (variable_check_key_format(key) != 0)
		return (-1);
	var = env->vars;
	while (var != NULL)
	{
		if (var->key != NULL && ft_strcmp(var->key, key) == 0)
		{
			variable_update(var, value, export);
			return (0);
		}
		var = var->next;
	}
	return (0);
}
