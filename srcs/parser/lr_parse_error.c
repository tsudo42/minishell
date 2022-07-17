/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_parse_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:23:08 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:55:19 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lr_func.h"

int	lr_parse_error(t_token_list *token)
{
	if (token->type == LR_NULL)
	{
		printf("syntax error: lexer error\n");
		return (256 + 2);
	}
	printf("syntax error near unexpected token ");
	if (token->type == LR_T_EOL)
		printf("`%s\'\n", "newline");
	else
		printf("`%s\'\n", token->str);
	return (256 + 2);
}
