/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/16 22:00:08 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>
#include <stdlib.h>

int	builtin_export_noarg(t_environ *env);

static int	export_format_checker(char *str)
{
	size_t	i;

	if (str == NULL || str[0] == '\0' || str[0] == '=')
		return (-1);
	if (!ft_isalpha(str[0]) && !((int)str[0] == '_'))
		return (-1);
	i = 1;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (0);
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) \
				&& !((int)str[i] == '_'))
			return (-1);
		i++;
	}
	return (0);
}

static int	export_val_append(char *key, char *value, t_environ *env)
{
	char	*joined;

	joined = ft_strjoin(variable_get(key, env), value);
	if (joined == NULL)
	{
		perror(EXPORT_ERRMSG ": malloc");
		exit(BUILTIN_FATALERROR);
	}
	variable_set(key, joined, 1, env);
	free(joined);
	return (BUILTIN_SUCCESS);
}

static int	export_val(char *str, t_environ *env)
{
	char	*eq;
	int		append;
	char	*value;

	eq = ft_strchr(str, '=');
	if (eq == NULL)
		return (variable_set(str, NULL, 1, env));
	append = 0;
	if (eq - str - 1 >= 0 && str[eq - str - 1] == '+')
		append = 1;
	value = eq + 1;
	*eq = '\0';
	if (append)
	{
		*(eq - 1) = '\0';
		return (export_val_append(str, value, env));
	}
	return (variable_set(str, value, 1, env));
}

static int	export_values(char **argv, t_environ *env)
{
	int	status;

	if (argv == NULL)
		return (0);
	argv++;
	status = BUILTIN_SUCCESS;
	while (*argv != NULL)
	{
		if (export_format_checker(*argv) != 0)
		{
			ft_dprintf(STDERR_FILENO, "%s: `%s\': not a valid identifier\n", \
				EXPORT_ERRMSG, *argv);
			status = BUILTIN_FAILURE;
		}
		else
			export_val(*argv, env);
		argv++;
	}
	return (status);
}

int	builtin_export(char **argv, t_environ *env)
{
	if (argv == NULL || *argv == NULL)
		return (BUILTIN_FAILURE);
	if (argv[1] == NULL)
		return (builtin_export_noarg(env));
	else
		return (export_values(argv, env));
}
