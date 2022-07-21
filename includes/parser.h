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

#ifndef PARSER_H
# define PARSER_H

# include "exec.h"

typedef enum e_lr_token_type {
	LR_NULL,
	LR_T_RED,
	LR_T_WORD,
	LR_T_OP,
	LR_T_PIPE,
	LR_T_LBRACE,
	LR_T_RBRACE,
	LR_T_EOL,
	LR_N_L,
	LR_N_P,
	LR_N_S,
	LR_N_C,
	LR_N_A,
	LR_N_D
}	t_lr_token_type;

/**
 * The liner list of token.
 * All token list should be end with LR_T_EOL or LR_NULL.
 * LR_NULL represents error and should be handled outside of lexer().
 *
 * `type` is token type described above.
 * `str` is the alloced string or NULL (only with LR_T_EOL or LR_NULL).
 * `next` is the pointer to next t_token_list or NULL.
 */
typedef struct s_token_list {
	t_lr_token_type		type;
	char				*str;
	struct s_token_list	*next;
}	t_token_list;

t_ast_l	*parser(t_token_list *token_list);

#endif /* PARSER_H */
