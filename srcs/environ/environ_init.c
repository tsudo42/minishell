/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/29 13:35:08 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "utils.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static t_var	*convert_str_to_var(const char *str)
{
	t_var	*var;
	char	*val;

	var = ft_x_malloc(sizeof(t_var), ENVIRON_ERRMSG ": malloc");
	val = ft_strchr(str, '=');
	if (val == NULL)
	{
		var->key = ft_strdup(str);
		var->value = NULL;
	}
	else
	{
		var->key = ft_strndup(str, val - str);
		var->value = ft_strdup(val + 1);
	}
	if (var->key == NULL || (val != NULL && var->value == NULL))
	{
		perror(ENVIRON_ERRMSG ": malloc");
		exit(1);
	}
	var->next = NULL;
	return (var);
}

static t_var	*init_environ_vars(void)
{
	extern char	**environ;
	t_var		*var_head;
	t_var		*var;

	if (environ == NULL || *environ == NULL)
		return (NULL);
	var = malloc(sizeof(t_var));
	if (var == NULL)
	{
		perror(ENVIRON_ERRMSG ": malloc");
		exit(1);
	}
	var_head = var;
	while (*environ != NULL)
	{
		var->next = convert_str_to_var(*environ);
		var = var->next;
		environ++;
	}
	var->next = NULL;
	return (var_head);
}

/**
 *  This function generates minishell environment used by malloc(3).
 *  This function should return non-NULL pointer.
 */
t_environ	*environ_init(void)
{
	t_environ	*env;

	env = malloc(sizeof(t_environ));
	if (env == NULL)
	{
		perror(ENVIRON_ERRMSG ": malloc");
		exit(1);
	}
	env->exit_status = 0;
	env->parent_pid = getpid();
	env->vars = init_environ_vars();
	return (env);
}
