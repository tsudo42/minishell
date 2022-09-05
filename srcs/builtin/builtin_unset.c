/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/31 15:08:02 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	unset_format_checker(char *str)
{
	size_t	i;

	if (str == NULL || str[0] == '\0' || str[0] == '=')
		return (-1);
	if (!ft_isalpha(str[0]) && !((int)str[0] == '_'))
		return (-1);
	i = 1;
	while (str[i] != '\0')
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) \
				&& !((int)str[i] == '_'))
			return (-1);
		i++;
	}
	return (0);
}

int	builtin_unset(char **argv, t_environ *env)
{
	int	status;

	status = 0;
	while (*argv != NULL)
	{
		if (unset_format_checker(*argv) != 0)
		{
			ft_dprintf(STDERR_FILENO, \
				"%s: `%s\' is not a valid identifier\n", *argv);
			status |= 1;
		}
		else
			variable_unset(*argv, env);
		argv++;
	}
	return (status);
}
