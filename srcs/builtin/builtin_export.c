/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/26 17:59:24 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	is_underbar(char c)
{
	if ((int)c == '_')
		return (true);
	return (false);
}

static int	export_value_checker(char *name, int len, char **argv)
{
	int	i;

	i = 1;
	while (i < len)
	{
		if (!ft_isalpha(name[0]) && !is_underbar(name[0]))
			break ;
		if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) \
				&& !is_underbar(name[i]))
			break ;
		i++;
	}
	if (i == len)
		return (STATUS_SUCCESS);
	ft_putstr_fd("export: '", STDERR_FILENO);
	ft_putstr_fd(*argv, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	free(name);
	return (STATUS_FAILURE);
}

static int	export_values(char **argv)
{
	char	*string;
	char	*value;
	int		status;

	status = STATUS_SUCCESS;
	while (*(++argv) != NULL)
	{
		string = ft_strdup(*argv);
		value = ft_strchr(string, '=');
		status = export_value_checker(string, value - string, argv);
		if (status == STATUS_FAILURE)
			break ;
		*value = '\0';
		if (value != NULL)
			ft_setenv(string, ++value, 1);
		free (string);
	}
	return (status);
}

int	builtin_export(char **argv)
{
	if (argv[1] == NULL)
		return (print_values());
	else
		return (export_values(argv));
}
