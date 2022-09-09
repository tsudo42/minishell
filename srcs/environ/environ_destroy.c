/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/29 13:35:08 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include <stdlib.h>

/**
 *  This function frees the minishell environ.
 *  This function always returns NULL.
 */
void	*environ_destroy(t_environ *env)
{
	t_var	*var;
	t_var	*next;

	var = env->vars;
	while (var != NULL)
	{
		next = var->next;
		free(var->key);
		free(var->value);
		free(var);
		var = next;
	}
	free(env);
	return (NULL);
}
