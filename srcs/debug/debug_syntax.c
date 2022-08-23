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
#include "libft.h"
#include <unistd.h>

int	debug_syntax(void)
{
	char			*line;
	t_token_list	*token;
	t_ast			*ast;

	write(1, "> ", 2);
	line = get_next_line_easy(0);
	while (line != NULL)
	{
		token = lexer(line);
		ast = parser(token);
		print_ast(ast);
		ast_free_l(ast);
		write(1, "> ", 2);
		line = get_next_line_easy(0);
	}
	return (0);
}
