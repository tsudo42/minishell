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

static const char	*token_list_get_typestr(t_lr_token_type type)
{
	if (type == LR_NULL)
		return ("LR_NULL");
	else if (type == LR_T_RED)
		return ("LR_T_RED");
	else if (type == LR_T_WORD)
		return ("LR_T_WORD");
	else if (type == LR_T_OP)
		return ("LR_T_OP");
	else if (type == LR_T_PIPE)
		return ("LR_T_PIPE");
	else if (type == LR_T_LBRACE)
		return ("LR_T_LBRACE");
	else if (type == LR_T_RBRACE)
		return ("LR_T_RBRACE");
	else if (type == LR_T_EOL)
		return ("LR_T_EOL");
	else if (type == LR_NULL)
		return ("LR_NULL");
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
		printf("  raw_str     : %s\n", list->str);
		list = list->next;
		i++;
	}
}
