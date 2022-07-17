/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_func.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef LR_FUNC_H
# define LR_FUNC_H

# include "lexer.h"

typedef enum e_ast_tree_type {
	AST_NULL,
	AST_L_AND,
	AST_L_OR,
	AST_L,
	AST_S_BRACES,
	AST_S_PIPE,
	AST_S,
	AST_C_ARGS,
	AST_C,
	AST_A_REDIRECT,
	AST_A
}	t_ast_tree_type;

typedef struct s_ast_tree {
	t_ast_tree_type		type;
	struct s_ast_tree	*left;
	struct s_ast_tree	*right;
}	t_ast_tree;

typedef enum e_lr_action_type {
	LR_ACT_SHIFT = 1,
	LR_ACT_REDUCE = 2,
	LR_ACT_ACCEPT = 3,
	LR_ACT_ERROR = -1
}	t_lr_action_type;

/* lr_table.c */
t_lr_action_type	lr_action(t_lr_token_type tok, int state);
int					lr_action_param(t_lr_token_type tok, int state);
int					lr_goto(t_lr_token_type tok, int state);

/* lr_rule.c */
int					lr_get_size_of_rule(int rule);
t_lr_token_type		lr_get_left_of_rule(int rule);

/* lr_apply_rule.c */
void				lr_apply_rule(int rule);

/* lr_parse_error.c */
int					lr_parse_error(t_token_list *token);

/* parsing is performed in the following internal function. */
int					lr_parse(t_token_list *token_list);

#endif /* LR_FUNC_H */
