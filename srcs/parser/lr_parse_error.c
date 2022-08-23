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

#include "lr_def.h"
#include "libft.h"
#include <unistd.h>

int	lr_parse_error(t_token_list *token)
{
	ft_putstr_fd(PARSER_ERRMSG ": ", STDERR_FILENO);
	if (token->type == LR_NULL)
	{
		ft_putendl_fd("syntax error: lexer error", STDERR_FILENO);
		return (256 + 2);
	}
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (token->type == LR_T_EOL)
		ft_putstr_fd("newline", STDERR_FILENO);
	else
		ft_putstr_fd(token->str, STDERR_FILENO);
	ft_putendl_fd("\'", STDERR_FILENO);
	return (256 + 2);
}
