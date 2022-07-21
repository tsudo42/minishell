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

#ifndef LR_DEF_H
# define LR_DEF_H

# include "parser.h"

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

/* lr_apply_rule.c */
void				lr_apply_rule(int rule);

/* lr_parse_error.c */
int					lr_parse_error(t_token_list *token);

/* parsing is performed in the following internal function. */
t_ast				*lr_parse(t_token_list *token_list);

#endif /* LR_DEF_H */
