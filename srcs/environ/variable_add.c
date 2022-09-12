/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:26:00 by hos               #+#    #+#             */
/*   Updated: 2022/09/12 15:08:08 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "utils.h"

/**
 *  This function creates a t_var to add key-value variable and
 *  return the t_var.
 *
 *  The key argument is checked via variable_check_key_format().
 *  This function exits with 1 when malloc(3) fails.

 *  If value argument is NULL, NULL is assigned to the value of 
 *  variable.
 *
 */
void	variable_add_back(t_environ *env, const char *key, const char *value)
{
	t_var	*var;

	var = env->vars;
	while (var->next)
		var = var->next;
	var->next = variable_add(key, value);
}

t_var	*variable_add(const char *key, const char *value)
{
	t_var		*var;

	if (variable_check_key_format(key) != 0)
		return (NULL);
	var = ft_x_malloc(sizeof(t_var), ENVIRON_ERRMSG ": malloc");
	var->key = ft_x_strdup(key, ENVIRON_ERRMSG ": malloc");
	if (value == NULL)
		var->value = NULL;
	else
		var->value = ft_x_strdup(value, ENVIRON_ERRMSG ": malloc");
	var->is_exported = 1;
	var->next = NULL;
	return (var);
}
