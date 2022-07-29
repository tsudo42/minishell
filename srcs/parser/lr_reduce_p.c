/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_reduce_p.c                                      :+:      :+:    :+:   */
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

/* P     : P PIPE S          (3 */
int	lr_parse_reduce_3(t_lr_stack *stack)
{
	t_ast_p	*p;
	t_ast_s	*s;

	s = lr_stack_pop(stack);
	free(lr_stack_pop(stack));
	p = lr_stack_pop(stack);
	\
	p = ast_make_p(p, AST_P_S, s);
	if (p == NULL)
		return (1);
	\
	lr_stack_push(stack, \
		LR_N_P, lr_goto(LR_N_P, lr_stack_peak(stack)->state), p);
	return (0);
}

/* P     | P PIPE C          (4 */
int	lr_parse_reduce_4(t_lr_stack *stack)
{
	t_ast_p	*p;
	t_ast_c	*c;

	c = lr_stack_pop(stack);
	free(lr_stack_pop(stack));
	p = lr_stack_pop(stack);
	\
	p = ast_make_p(p, AST_P_C, c);
	if (p == NULL)
		return (1);
	\
	lr_stack_push(stack, \
		LR_N_P, lr_goto(LR_N_P, lr_stack_peak(stack)->state), p);
	return (0);
}

/* P     |        S          (5 */
int	lr_parse_reduce_5(t_lr_stack *stack)
{
	t_ast_p	*p;
	t_ast_s	*s;

	s = lr_stack_pop(stack);
	\
	p = ast_make_p(NULL, AST_P_S, s);
	if (p == NULL)
		return (1);
	\
	lr_stack_push(stack, \
		LR_N_P, lr_goto(LR_N_P, lr_stack_peak(stack)->state), p);
	return (0);
}

/* P     |        C          (6 */
int	lr_parse_reduce_6(t_lr_stack *stack)
{
	t_ast_p	*p;
	t_ast_c	*c;

	c = lr_stack_pop(stack);
	\
	p = ast_make_p(NULL, AST_P_C, c);
	if (p == NULL)
		return (1);
	\
	lr_stack_push(stack, \
		LR_N_P, lr_goto(LR_N_P, lr_stack_peak(stack)->state), p);
	return (0);
}
