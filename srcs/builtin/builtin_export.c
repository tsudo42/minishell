/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/04 14:48:48 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_internal.h"

static int	export_value_checker(char *name, int len, char **argv)
{
	int	i;

	i = 1;
	while (i < len)
	{
		if (!ft_isalpha(name[0]) && !((int)name[0] == '_'))
			break ;
		if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) \
				&& !((int)name[i] == '_'))
			break ;
		i++;
	}
	if (i == len)
		return (STATUS_SUCCESS);
	ft_dprintf(STDERR_FILENO, \
		"%s: %s: not a valid identifier\n", EXPORT_ERRMSG, *argv);
	free(name);
	return (STATUS_FAILURE);
}

static int	export_values(char **argv)
{
	char	*string;
	char	*value;
	int		status;
	int		len;

	status = STATUS_SUCCESS;
	while (*(++argv) != NULL)
	{
		string = ft_x_strdup(*argv, EXPORT_ERRMSG);
		value = ft_strchr(string, '=');
		if (*(value - 1) == '+')
			len = value - string - 1;
		else
			len = value - string;
		status = export_value_checker(string, len, argv);
		if (status == STATUS_FAILURE)
			break ;
		if (++value != NULL)
			ft_putenv(string);
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
