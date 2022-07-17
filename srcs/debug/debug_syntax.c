/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "lexer.h"
#include "parser.h"

int	debug_syntax(void)
{
	char			*line;
	t_token_list	*token;

	write(1, "> ", 2);
	line = get_next_line_easy(0);
	while (line != NULL)
	{
		token = lexer(line);
		parser(token);
		write(1, "> ", 2);
		line = get_next_line_easy(0);
	}
	return (0);
}
