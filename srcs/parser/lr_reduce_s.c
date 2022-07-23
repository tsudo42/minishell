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
int	lr_parse_reduce_7(t_lr_stack *stack)
{
	t_ast_s	*s;
	t_ast_l	*l;
	t_ast_d	*d;

	d = lr_stack_pop(stack);
	free(lr_stack_pop(stack));
	l = lr_stack_pop(stack);
	free(lr_stack_pop(stack));
	\
	s = ast_make_s(l, d);
	if (s == NULL)
		return (1);
	\
	lr_stack_push(stack, \
		LR_N_S, lr_goto(LR_N_S, lr_stack_peak(stack)->state), s);
	return (0);
}

/* S     | LBRACE L RBRACE   (8 */
int	lr_parse_reduce_8(t_lr_stack *stack)
{
	t_ast_s	*s;
	t_ast_l	*l;

	free(lr_stack_pop(stack));
	l = lr_stack_pop(stack);
	free(lr_stack_pop(stack));
	\
	s = ast_make_s(l, NULL);
	if (s == NULL)
		return (1);
	\
	lr_stack_push(stack, \
		LR_N_S, lr_goto(LR_N_S, lr_stack_peak(stack)->state), s);
	return (0);
}
