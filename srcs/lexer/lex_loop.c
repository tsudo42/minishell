/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:23:08 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:55:19 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"
#include "libft.h"

static t_token_list	*loop_return(char **input, size_t len, t_lr_token_type type)
{
	char			*str;
	t_token_list	*token;

	str = ft_strndup(*input, len);
	if (str == NULL)
		return (NULL);
	token = token_list_new(type, str);
	*input += len;
	return (token);
}

static size_t	redstr_len(char *str)
{
	size_t	len;

	len = ft_strspn(str, LEX_NUM);
	if ((ft_strncmp(str + len, LEX_REDAPP, 2) == 0) || \
		(ft_strncmp(str + len, LEX_HERE, 2) == 0))
		return (len + 2);
	if ((ft_strncmp(str + len, LEX_REDIN, 1) == 0) || \
		(ft_strncmp(str + len, LEX_REDOUT, 1) == 0))
		return (len + 1);
	return (0);
}

static t_lr_token_type	lex_quote(char **input)
{
	char	quote[2];

	quote[0] = **input;
	quote[1] = '\0';
	*input += 1;
	*input += ft_strcspn(*input, quote);
	if (**input == quote[0])
	{
		(*input)++;
		return (LR_T_WORD);
	}
	else
	{
		ft_putstr_fd(LEXER_ERRMSG ": unexpected EOF", STDERR_FILENO);
		ft_putstr_fd("while looking for matching `", STDERR_FILENO);
		ft_putchar_fd(quote[0], STDERR_FILENO);
		ft_putendl_fd("\'", STDERR_FILENO);
		return (LR_NULL);
	}
}

/* **input should not be '\0'. */

static t_token_list	*lex_word(char **input, t_lr_token_type type)
{
	char	*start_ptr;

	start_ptr = *input;
	while (**input != '\0')
	{
		if (ft_strchr(LEX_EOW, **input) != NULL)
			break ;
		else if (**input == '\'' || **input == '\"')
			type = lex_quote(input);
		else if (ft_isdigit(**input))
		{
			if (redstr_len(*input) > 0)
				break ;
			else
				(*input) += ft_strspn(*input, LEX_NUM);
		}
		else
			(*input)++;
	}
	return (loop_return(&start_ptr, *input - start_ptr, type));
}

/* assuming sizeof(char) == 1. */
/* skipping newline check. */

t_token_list	*lex_loop(char **input)
{
	size_t	len;

	(*input) += ft_strspn(*input, LEX_SEP);
	if (**input == '\0')
		return (token_list_new(LR_T_EOL, NULL));
	if (ft_strncmp(*input, LEX_ANDAND, sizeof(LEX_ANDAND) - 1) == 0)
		return (loop_return(input, sizeof(LEX_ANDAND) - 1, LR_T_OP));
	if (ft_strncmp(*input, LEX_OROR, sizeof(LEX_OROR) - 1) == 0)
		return (loop_return(input, sizeof(LEX_OROR) - 1, LR_T_OP));
	if (ft_strncmp(*input, LEX_PIPE, sizeof(LEX_PIPE) - 1) == 0)
		return (loop_return(input, sizeof(LEX_PIPE) - 1, LR_T_PIPE));
	if (ft_strncmp(*input, LEX_LBRACE, sizeof(LEX_LBRACE) - 1) == 0)
		return (loop_return(input, sizeof(LEX_LBRACE) - 1, LR_T_LBRACE));
	if (ft_strncmp(*input, LEX_RBRACE, sizeof(LEX_RBRACE) - 1) == 0)
		return (loop_return(input, sizeof(LEX_RBRACE) - 1, LR_T_RBRACE));
	len = redstr_len(*input);
	if (len > 0)
		return (loop_return(input, len, LR_T_RED));
	if (ft_strchr(LEX_EOW, **input) != NULL)
		return (lex_error_token(**input));
	return (lex_word(input, LR_T_WORD));
}
