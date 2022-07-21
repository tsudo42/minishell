/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:23:08 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:55:19 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lr_internal.h"
#include "lexer.h"

t_ast_l	*parser(t_token_list *token_list)
{
	t_ast_l	*ast_root;

	if (token_list == NULL)
		return (NULL);
	ast_root = lr_parse(token_list);
	token_list_free(&token_list);
	return (ast_root);
}
