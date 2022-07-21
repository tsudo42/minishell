/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_reduce_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:23:08 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:55:19 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lr_internal.h"
#include "exec.h"
#include "libft.h"

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

/* S     : LBRACE L RBRACE D (7 */
void	lr_parse_reduce_7(t_lr_stack *stack)
{
	t_ast_s	*s;

	s = ft_x_malloc(sizeof(t_ast_s), PARSER_ERRMSG);
	\
	s->d = lr_stack_pop(stack);
	free(lr_stack_pop(stack));
	s->l = lr_stack_pop(stack);
	free(lr_stack_pop(stack));
	\
	lr_stack_push(stack, \
		LR_N_S, lr_goto(LR_N_S, lr_stack_peak(stack)->state), s);
}

/* S     | LBRACE L RBRACE   (8 */
void	lr_parse_reduce_8(t_lr_stack *stack)
{
	t_ast_s	*s;

	s = ft_x_malloc(sizeof(t_ast_s), PARSER_ERRMSG);
	\
	free(lr_stack_pop(stack));
	s->l = lr_stack_pop(stack);
	free(lr_stack_pop(stack));
	\
	s->d = NULL;
	\
	lr_stack_push(stack, \
		LR_N_S, lr_goto(LR_N_S, lr_stack_peak(stack)->state), s);
}
