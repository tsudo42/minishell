/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

/**
 * NULL_TOKEN means error.
 * currently only unclosed quotation(single/double) occurs this error.
 * AND/OR is not currently used.
 * EOF means '\0'.
 */
typedef enum e_token_type {
	NULL_TOKEN,
	SQ_STRING,
	DQ_STRING,
	STRING,
	RED_IN,
	RED_OUT,
	RED_OUT_APPEND,
	RED_IN_HEREDOC,
	PIPE,
	AND,
	OR,
	BRACE_BEGIN,
	BRACE_END,
	NEWLINE,
	SPACE_TAB,
	EOF_TOKEN
}	t_token_type;

/**
 * The liner list of token.
 * All token list should be end with EOF_TOKEN or NULL_TOKEN.
 * NULL_TOKEN represents error and should be handled outside of lexer().
 *
 * `type` is token type described above.
 * `raw_str` is the alloced string if token type is STRING/SQ_STRING/
 * DQ_STRING/SPACE_TAB.
 * otherwise, NULL.
 * `next` is the pointer to next t_token_list or NULL.
 */
typedef struct s_token_list {
	t_token_type		type;
	char				*raw_str;
	void				*other_param;
	struct s_token_list	*next;
}	t_token_list;

/**
 * Tokenize the input line and generate the token list.
 * input should be end with the newline.
 * A list of tokens will be returned which shuold be freed.
 *
 * input will be freed even if lexer() encounters error.
 *
 * lexer() returns token list end with type EOF_TOKEN or NULL_TOKEN, or NULL.
 * Token list end with EOF_TOKEN means successful.
 * Token list end with NULL_TOKEN means fail in tokenization.
 * NULL means malloc(3) error.
 */
t_token_list	*lexer(char *input);

/**
 * Frees the token list.
 */
void			token_list_free(t_token_list *token_list);

/**
 * Prints token list via printf.
 * For DEBUG.
 */
void			token_list_print(t_token_list *list);

#endif /* LEXER_H */
