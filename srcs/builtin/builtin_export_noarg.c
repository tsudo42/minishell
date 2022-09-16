/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_noarg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 19:05:12 by hos               #+#    #+#             */
/*   Updated: 2022/09/16 16:40:49 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	cmp_key(void *p1, void *p2)
{
	t_var	*v1;
	t_var	*v2;

	v1 = p1;
	v2 = p2;
	return (ft_strcmp(v1->key, v2->key));
}

static t_list	*init_list(t_environ *env)
{
	t_list	*list;
	t_var	*var;

	if (!env)
		return (NULL);
	var = env->vars;
	list = ft_lstnew(var);
	if (var->next != NULL)
		var = var->next;
	while (var->next != NULL)
	{
		ft_lstadd_back(&list, ft_lstnew(var));
		var = var->next;
	}
	return (list);
}

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

int	builtin_export_noarg(t_environ *env)
{
	return (print_values(env));
}
