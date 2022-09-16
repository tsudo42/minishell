/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/16 16:40:03 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	print_variable(t_var	*content)
{
	char	*value;

	if (content->key != NULL && content->is_exported)
	{
		ft_dprintf(STDOUT_FILENO, "declare -x %s", content->key);
		if (content->value != NULL)
		{
			write(STDOUT_FILENO, "=\"", 2);
			value = content->value;
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
	t_list	*list;
	t_list	*list_head;

	list_head = init_list(env);
	if (list_head)
		ft_lstmsort(&list_head, (void *)cmp_key);
	list = list_head;
	while (list != NULL)
	{
		print_variable((t_var *)list->content);
		list = list->next;
	}
	ft_lstclear(&list, NULL);
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
	if (argv == NULL || *argv == NULL)
		return (STATUS_FAILURE);
	if (argv[1] == NULL)
		return (print_values(env));
	else
		return (export_values(argv, env));
}
