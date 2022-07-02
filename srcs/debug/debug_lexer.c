/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "debug.h"

/**
 * Function to debug lexer().
 * Input via stdin and print the token list.
 * Always returns 0.
 */
int	debug_lexer(void)
{
	char			*input;
	t_token_list	*list;

	input = get_next_line_easy(0);
	while (input != NULL)
	{
		list = lexer(input);
		token_list_print(list);
		token_list_free(&list);
		input = get_next_line_easy(0);
	}
	return (0);
}
