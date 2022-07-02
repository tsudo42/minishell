/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static const char	*token_list_get_typestr(t_token_type type);
static const char	*token_list_get_typestr_2(t_token_type type);

static const char	*token_list_get_typestr(t_token_type type)
{
	if (type == NULL_TOKEN)
		return ("NULL_TOKEN");
	else if (type == SQ_STRING)
		return ("SQ_STRING");
	else if (type == DQ_STRING)
		return ("DQ_STRING");
	else if (type == STRING)
		return ("STRING");
	else if (type == RED_IN)
		return ("RED_IN");
	else if (type == RED_OUT)
		return ("RED_OUT");
	else if (type == RED_OUT_APPEND)
		return ("RED_OUT_APPEND");
	else if (type == RED_IN_HEREDOC)
		return ("RED_IN_HEREDOC");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == AND)
		return ("AND");
	else if (type == OR)
		return ("OR");
	else
		return (token_list_get_typestr_2(type));
}

static const char	*token_list_get_typestr_2(t_token_type type)
{
	if (type == BRACE_BEGIN)
		return ("BRACE_BEGIN");
	else if (type == BRACE_END)
		return ("BRACE_END");
	else if (type == NEWLINE)
		return ("NEWLINE");
	else if (type == SPACE_TAB)
		return ("SPACE_TAB");
	else if (type == EOF_TOKEN)
		return ("EOF_TOKEN");
	else
		return ("????UNDEFINED????");
}

/**
 * Prints token list via printf.
 * For DEBUG.
 */
void	token_list_print(t_token_list *list)
{
	size_t	i;

	if (list == NULL)
	{
		printf("list is NULL\n");
		return ;
	}
	i = 0;
	while (list != NULL)
	{
		printf("<< list[%zu] >>\n", i);
		printf("  type        : %s\n", token_list_get_typestr(list->type));
		printf("  raw_str     : %s\n", list->raw_str);
		printf("  other_param : %p\n", list->other_param);
		list = list->next;
		i++;
	}
}
