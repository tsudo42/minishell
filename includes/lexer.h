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
# include "utils.h"
# include "parser.h"

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
 * Argument must be a pointer to token list.
 * usage: token_list_free(&token_list);
 */
void			token_list_free(t_token_list **token_list_ptr);

/**
 * Prints token list via printf.
 * For DEBUG.
 */
void			token_list_print(t_token_list *list);

#endif /* LEXER_H */
