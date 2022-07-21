/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_internal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef LR_INTERNAL_H
# define LR_INTERNAL_H

# include "lr_def.h"
# include "utils.h"
# include <stdlib.h>

# define PARSER_ERRMSG "minishell"

typedef struct s_lr_node {
	t_lr_token_type	type;
	int				state;
	void			*content;
}	t_lr_node;

typedef struct s_lr_stack {
	size_t		size;
	size_t		alloc_size;
	t_lr_node	*c;
}	t_lr_stack;

/* lr_stack.c */
t_lr_stack		*lr_stack_init(void);
void			lr_stack_push(t_lr_stack *stack, \
	t_lr_token_type type, int state, void *content);
void			*lr_stack_pop(t_lr_stack *stack);
t_lr_node		*lr_stack_peak(t_lr_stack *stack);
void			lr_stack_terminate(t_lr_stack **stack_ptr);

/**
L     : L OP P            (1
      |      P            (2
      ;
P     : P PIPE S          (3
      | P PIPE C          (4
      |        S          (5
      |        C          (6
      ;
S     : LBRACE L RBRACE D (7
      | LBRACE L RBRACE   (8
      ;
C     : C A               (9
      |   A               (10
      ;
A     : RED WORD          (11
      |     WORD          (12
      ;
D     : D RED WORD        (13
      |   RED WORD        (14
      ;
*/

void			lr_parse_reduce_1(t_lr_stack *stack);
void			lr_parse_reduce_2(t_lr_stack *stack);
void			lr_parse_reduce_3(t_lr_stack *stack);
void			lr_parse_reduce_4(t_lr_stack *stack);
void			lr_parse_reduce_5(t_lr_stack *stack);
void			lr_parse_reduce_6(t_lr_stack *stack);
void			lr_parse_reduce_7(t_lr_stack *stack);
void			lr_parse_reduce_8(t_lr_stack *stack);
void			lr_parse_reduce_9(t_lr_stack *stack);
void			lr_parse_reduce_10(t_lr_stack *stack);
void			lr_parse_reduce_11(t_lr_stack *stack);
void			lr_parse_reduce_12(t_lr_stack *stack);
void			lr_parse_reduce_13(t_lr_stack *stack);
void			lr_parse_reduce_14(t_lr_stack *stack);

#endif /* LR_INTERNAL_H */
