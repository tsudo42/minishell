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

int	lr_parse_error(t_token_list *token)
{
	if (token->type == LR_NULL)
	{
		ft_putendl_fd("syntax error: lexer error", 2);
		return (256 + 2);
	}
	ft_putstr_fd("syntax error near unexpected token `", 2);
	if (token->type == LR_T_EOL)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(token->str, 2);
	ft_putendl_fd("\'", 2);
	return (256 + 2);
}
