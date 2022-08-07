/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_reduce_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:23:08 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:55:19 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lr_internal.h"
//#include "exec.h"
//#include "lexer.h"
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

/* C     : C A               (9 */
int	lr_parse_reduce_9(t_lr_stack *stack)
{
	t_ast_c	*c;
	t_ast_a	*a;
	t_ast_d	*d;

	a = lr_stack_pop(stack);
	c = lr_stack_pop(stack);
	\
	if (a->red == NULL)
		c = ast_make_c(c, a, NULL);
	else
	{
		d = ast_convert_a_to_d(a);
		if (d == NULL)
		{
			ast_free_c(c);
			return (1);
		}
		c = ast_make_c(c, NULL, d);
	}
	if (c == NULL)
		return (1);
	\
	lr_stack_push(stack, \
		LR_N_C, lr_goto(LR_N_C, lr_stack_peak(stack)->state), c);
	return (0);
}

/* C     |   A               (10 */
int	lr_parse_reduce_10(t_lr_stack *stack)
{
	t_ast_c	*c;
	t_ast_a	*a;
	t_ast_d	*d;

	a = lr_stack_pop(stack);
	\
	if (a->red == NULL)
		c = ast_make_c(NULL, a, NULL);
	else
	{
		d = ast_convert_a_to_d(a);
		if (d == NULL)
			return (1);
		c = ast_make_c(NULL, NULL, d);
	}
	if (c == NULL)
		return (1);
	\
	lr_stack_push(stack, \
		LR_N_C, lr_goto(LR_N_C, lr_stack_peak(stack)->state), c);
	return (0);
}
