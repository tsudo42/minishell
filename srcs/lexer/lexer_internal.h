/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H

# include "lexer.h"

/* lex_loop.c */
t_token_list	*lex_loop(char **input);
/* lex_string.c */
t_token_list	*lex_space_tab(char **input);
/* lex_string.c */
t_token_list	*lex_string(char **input);
/* lex_redirection.c */
t_token_list	*lex_less(char **input);
/* lex_redirection.c */
t_token_list	*lex_greater(char **input);
/* lex_quote.c */
t_token_list	*lex_single_quote(char **input);
/* lex_quote.c */
t_token_list	*lex_double_quote(char **input);

/* token_list_utils.c */
t_token_list	*token_list_new( \
	t_token_type type, char *raw_str, void *other_param);
/* token_list_utils.c */
t_token_list	*token_list_append( \
	t_token_list *head, t_token_type type, char *raw_str, void *other_param);
/* token_list_utils.c */
t_token_list	*token_list_join(t_token_list *head, t_token_list *tail);

#endif /* LEXER_INTERNAL_H */
