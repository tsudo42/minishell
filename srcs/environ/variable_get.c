/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/31 15:09:46 by hosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "libft.h"

/**
 *  This function gets string of variable selected by key if found.
 *  Otherwise, NULL is returned.
 *
 *  The returned value of variable should not be modified or freed.
 *
 *  Argument key is checked via variable_check_key_format().
 */
char	*variable_get(const char *key, t_environ *env)
{
	t_var	*var;

	if (variable_check_key_format(key) != 0)
		return (NULL);
	var = env->vars;
	while (var != NULL)
	{
		if (var->key != NULL && ft_strcmp(var->key, key) == 0)
			return (var->value);
		var = var->next;
	}
	return (NULL);
}
