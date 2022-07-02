/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

t_token_list	*lex_less(char **input)
{
	if (**input != '<')
		return (NULL);
	if (*(*input + 1) == '<')
	{
		(*input) += 2;
		return (token_list_new(RED_IN_HEREDOC, strdup("<<"), NULL));
	}
	else
	{
		(*input) += 1;
		return (token_list_new(RED_IN, strdup("<"), NULL));
	}
}

t_token_list	*lex_greater(char **input)
{
	if (**input != '>')
		return (NULL);
	if (*(*input + 1) == '>')
	{
		(*input) += 2;
		return (token_list_new(RED_OUT_APPEND, strdup(">>"), NULL));
	}
	else
	{
		(*input) += 1;
		return (token_list_new(RED_OUT, strdup(">"), NULL));
	}
}
