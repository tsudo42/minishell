/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_internal.h"

/**
 * Checks if tokenization to be end.
 */
static int	if_continue_lex(t_token_list *token)
{
	if (token == NULL)
		return (0);
	if (token->type == NULL_TOKEN || token->type == EOF_TOKEN)
		return (0);
	else
		return (1);
}

/**
 * Tokenize the input line and generate the token list.
 * input should be end with the newline.
 * A list of tokens will be returned which shuold be freed.
 *
 * input will be freed even if lexer() encounters error.
 *
 * lexer() returns token list end with type EOF_TOKEN or NULL_TOKEN, or NULL.
 * Token list end with EOF_TOKEN when successful.
 * Token list end with NULL_TOKEN when fail in tokenization.
 * NULL when malloc(3) error.
 */
t_token_list	*lexer(char *input)
{
	char			*input_to_free;
	t_token_list	*token_list_head;
	t_token_list	*token_list_append;

	if (input == NULL)
		return (NULL);
	\
	input_to_free = input;
	token_list_head = NULL;
	\
	token_list_append = lex_loop(&input);
	while (if_continue_lex(token_list_append))
	{
		token_list_head = token_list_join(token_list_head, token_list_append);
		token_list_append = lex_loop(&input);
	}
	if (token_list_append == NULL)
		token_list_free(&token_list_head);
	else
		token_list_head = token_list_join(token_list_head, token_list_append);
	free(input_to_free);
	return (token_list_head);
}
