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
	if (argv == NULL || *argv == NULL)
		return (BUILTIN_FAILURE);
	if (argv[1] == NULL)
		return (builtin_export_noarg(env));
	else
		return (export_values(argv, env));
}
