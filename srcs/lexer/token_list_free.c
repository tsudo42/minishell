/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * Frees the token list.
 * Argument must be a pointer to token list.
 * usage: token_list_free(&token_list);
 */
void	token_list_free(t_token_list **token_list_ptr)
{
	t_token_list	*token_list;
	t_token_list	*next;

	token_list = *token_list_ptr;
	while (token_list != NULL)
	{
		next = token_list->next;
		free(token_list->str);
		token_list->str = NULL;
		free(token_list);
		token_list = next;
	}
	*token_list_ptr = NULL;
}
