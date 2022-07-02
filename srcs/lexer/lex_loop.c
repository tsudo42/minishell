/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

static t_token_list	*lex_char(char **input)
{
	if (**input == '|')
	{
		(*input)++;
		return (token_list_new(PIPE, NULL, NULL));
	}
	else if (**input == '\n')
	{
		(*input)++;
		return (token_list_new(NEWLINE, NULL, NULL));
	}
	else if (**input == '\0')
	{
		(*input)++;
		return (token_list_new(EOF_TOKEN, NULL, NULL));
	}
	else
		return (lex_string(input));
}

t_token_list	*lex_loop(char **input)
{
	if (**input == ' ' || **input == '\t')
		return (lex_space_tab(input));
	else if (**input == '\'')
		return (lex_single_quote(input));
	else if (**input == '\"')
		return (lex_double_quote(input));
	else if (**input == '<')
		return (lex_less(input));
	else if (**input == '>')
		return (lex_greater(input));
	else
		return (lex_char(input));
}
