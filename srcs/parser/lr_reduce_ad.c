/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_reduce_ad.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:23:08 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:55:19 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lr_internal.h"
#include "ast.h"

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

/* A     : RED WORD          (11 */
int	lr_parse_reduce_11(t_lr_stack *stack)
{
	t_ast_a	*a;
	char	*red;
	char	*word;

	word = lr_stack_pop(stack);
	red = lr_stack_pop(stack);
	\
	a = ast_make_a(red, word);
	if (a == NULL)
		return (1);
	\
	lr_stack_push(stack, \
		LR_N_A, lr_goto(LR_N_A, lr_stack_peak(stack)->state), a);
	return (0);
}

/* A     |     WORD          (12 */
int	lr_parse_reduce_12(t_lr_stack *stack)
{
	t_ast_a	*a;
	char	*word;

	word = lr_stack_pop(stack);
	\
	a = ast_make_a(NULL, word);
	if (a == NULL)
		return (1);
	\
	lr_stack_push(stack, \
		LR_N_A, lr_goto(LR_N_A, lr_stack_peak(stack)->state), a);
	return (0);
}

/* D     : D RED WORD        (13 */
int	lr_parse_reduce_13(t_lr_stack *stack)
{
	t_ast_d	*d;
	char	*red;
	char	*word;

	word = lr_stack_pop(stack);
	red = lr_stack_pop(stack);
	d = lr_stack_pop(stack);
	\
	d = ast_make_d(d, red, word);
	if (d == NULL)
		return (1);
	\
	lr_stack_push(stack, \
		LR_N_D, lr_goto(LR_N_D, lr_stack_peak(stack)->state), d);
	return (0);
}

/* D     |   RED WORD        (14 */
int	lr_parse_reduce_14(t_lr_stack *stack)
{
	t_ast_d	*d;
	char	*red;
	char	*word;

	word = lr_stack_pop(stack);
	red = lr_stack_pop(stack);
	\
	d = ast_make_d(NULL, red, word);
	if (d == NULL)
		return (1);
	\
	lr_stack_push(stack, \
		LR_N_D, lr_goto(LR_N_D, lr_stack_peak(stack)->state), d);
	return (0);
}
