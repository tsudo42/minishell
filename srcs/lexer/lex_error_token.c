/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_error_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:23:08 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:55:19 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"
#include "libft.h"
#include <unistd.h>

t_token_list	*lex_error_token(char token)
{
	ft_dprintf(STDERR_FILENO, \
		"%s: unrecognized character token `%s\'\n", LEXER_ERRMSG, token);
	return (token_list_new(LR_NULL, NULL));
}
