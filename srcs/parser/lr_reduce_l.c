/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_reduce_l.c                                      :+:      :+:    :+:   */
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

static t_ast_l_type	get_ast_l_type(char *op)
{
	t_ast_l_type	op_type;

	if (ft_strncmp("&&", op, sizeof("&&")) == 0)
		op_type = AST_L_AND;
	else if (ft_strncmp("||", op, sizeof("||")) == 0)
		op_type = AST_L_OR;
	else
		op_type = AST_L_COLON;
	free(op);
	return (op_type);
}

/* L     : L OP P            (1 */
int	lr_parse_reduce_1(t_lr_stack *stack)
{
	t_ast_l			*l;
	t_ast_l_type	type;
	t_ast_p			*p;

	p = lr_stack_pop(stack);
	type = get_ast_l_type(lr_stack_pop(stack));
	l = lr_stack_pop(stack);
	\
	l = ast_make_l(l, type, p);
	if (l == NULL)
		return (1);
	\
	lr_stack_push(stack, \
		LR_N_L, lr_goto(LR_N_L, lr_stack_peak(stack)->state), l);
	return (0);
}

/* L      |      P            (2 */
int	lr_parse_reduce_2(t_lr_stack *stack)
{
	t_ast_l			*l;
	t_ast_p			*p;

	p = lr_stack_pop(stack);
	\
	l = ast_make_l(NULL, AST_L_AND, p);
	if (l == NULL)
		return (1);
	\
	lr_stack_push(stack, \
		LR_N_L, lr_goto(LR_N_L, lr_stack_peak(stack)->state), l);
	return (0);
}
