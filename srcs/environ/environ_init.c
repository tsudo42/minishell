/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/09 12:18:46 by hos              ###   ########.fr       */
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
	var->is_exported = 1;
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
	var = convert_str_to_var(*environ);
	var_head = var;
	environ++;
	while (*environ != NULL)
	{
		var->next = convert_str_to_var(*environ);
		var = var->next;
		environ++;
	}
	var->next = NULL;
	return (var_head);
}

static t_var	*add_initial_env(void)
{
	t_var	*var;
	char	buf[PATH_MAX];

	var = variable_add("SHLVL", "1");
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		perror(ENVIRON_ERRMSG ": getcwd");
		exit (1);
	}
	var->next = variable_add("PWD", buf);
	var->next->next = variable_add("OLDPWD", NULL);
	return (var);
}

/**
 *  This function generates minishell environment used by malloc(3).
 *  This function should return non-NULL pointer.
 */
t_environ	*environ_init(void)
{
	t_environ	*env;
	char		*s;

	env = malloc(sizeof(t_environ));
	if (env == NULL)
	{
		perror(ENVIRON_ERRMSG ": malloc");
		exit(1);
	}
	env->exit_status = 0;
	env->parent_pid = getpid();
	env->vars = init_environ_vars();
	if (env->vars == NULL)
		env->vars = add_initial_env();
	else
	{
		s = variable_get("SHLVL", env);
		if (s != NULL)
			variable_set("SHLVL", ft_itoa(ft_atoi(s) + 1), 1, env);
		variable_set("OLDPWD", NULL, 1, env);
		variable_unset("_", env);
	}
	return (env);
}
