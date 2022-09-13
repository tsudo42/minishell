/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/13 11:08:59 by hos              ###   ########.fr       */
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

	var = (t_var *)malloc(sizeof(t_var));
	if (var == NULL)
	{
		perror(ENVIRON_ERRMSG ": malloc");
		exit (1);
	}
	var->key = NULL;
	var->value = NULL;
	var->is_exported = 0;
	var->next = NULL;
	if (environ == NULL || *environ == NULL)
		return (var);
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

static void	update_pwd(t_environ *env)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		perror(ENVIRON_ERRMSG ": getcwd");
		exit (1);
	}
	if (variable_get("PWD", env) != NULL)
		variable_set("OLDPWD", variable_get("PWD", env), 1, env);
	else
		variable_set("OLDPWD", NULL, 1, env);
	variable_set("PWD", buf, 1, env);
}

static void	update_shlvl(t_environ *env)
{
	char	*num;
	char	*s;

	s = variable_get("SHLVL", env);
	if (!s)
		variable_set("SHLVL", "1", 1, env);
	else
	{
		if (ft_atoi(s) > 1000)
		{
			perror(ENVIRON_ERRMSG ": SHLVL");
			num = ft_itoa(1);
		}
		else
		{
			num = ft_itoa(ft_atoi(s) + 1);
			if (num == NULL)
			{
				perror(ENVIRON_ERRMSG ": malloc");
				exit (1);
			}
		}
		variable_set("SHLVL", num, 1, env);
		free (num);
	}
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
	update_shlvl(env);
	update_pwd(env);
	variable_unset("_", env);
	return (env);
}
