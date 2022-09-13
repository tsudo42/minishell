/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/13 08:44:18 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	print_variable(t_var *var)
{
	char	*value;

	if (var->key != NULL && var->is_exported)
	{
		ft_dprintf(STDOUT_FILENO, "declare -x %s", var->key);
		if (var->value != NULL)
		{
			write(STDOUT_FILENO, "=\"", 2);
			value = var->value;
			while (*value != '\0')
			{
				if (*value == '\"' || *value == '\\' || \
					*value == '$' || *value == '`')
					write(STDOUT_FILENO, "\\", 1);
				write(STDOUT_FILENO, value, 1);
				value++;
			}
			write(STDOUT_FILENO, "\"", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

static int	print_values(t_environ *env)
{
	t_var	*var;

	var = env->vars;
	while (var != NULL)
	{
		print_variable(var);
		var = var->next;
	}
	return (0);
}

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
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) \
				&& !((int)str[i] == '_'))
			return (-1);
		i++;
	}
	return (0);
}

static int	export_values(char **argv, t_environ *env)
{
	char	*key;
	char	*value;

	if (argv == NULL)
		return (0);
	argv++;
	while (*argv != NULL)
	{
		if (export_format_checker(*argv) != 0)
		{
			ft_dprintf(STDERR_FILENO, "%s: `%s\': not a valid identifier\n", \
				EXPORT_ERRMSG, *argv);
			return (1);
		}
		key = ft_strtok(*argv, "=");
		value = ft_strtok(NULL, "");
		variable_set(key, value, 1, env);
		argv++;
	}
	return (0);
}

int	builtin_export(char **argv, t_environ *env)
{
	if (argv[1] == NULL)
		return (print_values(env));
	else
		return (export_values(argv, env));
}
