/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/31 15:00:13 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_env(char **argv, t_environ *env)
{
	t_var	*var;

	(void)argv;
	var = env->vars;
	while (var != NULL)
	{
		if (var->key != NULL && var->value != NULL && var->is_exported)
			ft_dprintf(STDOUT_FILENO, "%s=%s\n", var->key, var->value);
		var = var->next;
	}
	return (STATUS_SUCCESS);
}
