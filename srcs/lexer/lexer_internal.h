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

# define LEX_SEP	" \n"           /* separator          */
# define LEX_ANDAND	"&&"            /* and operator       */
# define LEX_OROR	"||"            /* or operator        */
# define LEX_PIPE	"|"             /* pipe character     */
# define LEX_LBRACE	"("             /* brace begin        */
# define LEX_RBRACE	")"             /* brace end          */
# define LEX_REDIN	"<"             /* redirect in        */
# define LEX_REDOUT	">"             /* redirect out       */
# define LEX_REDAPP	">>"            /* redirect append    */
# define LEX_HERE	"<<"            /* heredoc            */
# define LEX_NUM	"0123456789"    /* set of numbers     */
# define LEX_EOW	" \n&|;()<>"    /* set of end of word */

/* lex_loop.c */
t_token_list	*lex_loop(char **input);

/* lex_error_token.c */
t_token_list	*lex_error_token(char token);

/* token_list_utils.c */
t_token_list	*token_list_new(t_lr_token_type type, char *str);
/* token_list_utils.c */
t_token_list	*token_list_append( \
	t_token_list *head, t_lr_token_type type, char *str);
/* token_list_utils.c */
t_token_list	*token_list_join(t_token_list *head, t_token_list *tail);

#endif /* LEXER_INTERNAL_H */
